#include <Arduino.h>
#include <ADXL345.h>
#include <activity_tracking_inferencing.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>

/** Struct to link sensor axis name to sensor value function */
typedef struct
{
    const char *name;
    float *value;
    int8_t status; // -1 not used, 0 used(uninitialized), 1 used(initialized), 2 data sampled
} eiSensors;

/* Constant defines -------------------------------------------------------- */
#define CONVERT_G_TO_MS2 9.80665f
#define MAX_ACCEPTED_RANGE 2.0f
/** Number of sensor axes used */
#define N_SENSORS 3 // Update the number of sensors

/* Forward declarations ------------------------------------------------------- */
float ei_get_sign(float number);
static bool ei_connect_fusion_list(const char *input_list);
static int8_t ei_find_axis(const char *axis_name);
void set_up_ADXL345(); // Ensure these functions are defined
void run_ADXL345();
void data_ADXL345(void);
void run_Model(void);

/* Private variables ------------------------------------------------------- */
static const bool debug_nn = false; // Set this to true to see e.g. features generated from the raw signal
static float data[N_SENSORS];
static int8_t fusion_sensors[N_SENSORS];
static int fusion_ix = 0;

/** Used sensors value function connected to label name */
eiSensors sensors[] = {
    {"accX", &X_out, -1},
    {"accY", &Y_out, -1},
    {"accZ", &Z_out, -1}};

void data_ADXL345(void);

void setup()
{
    /* Init serial */
    Serial.begin(115200);
    set_up_ADXL345();

    // Comment out the below line to cancel the wait for USB connection (needed for native USB)
    while (!Serial)
        ;
    Serial.println("Edge Impulse Sensor Fusion Inference\r\n");

    /* Connect used sensors */
    if (ei_connect_fusion_list(EI_CLASSIFIER_FUSION_AXES_STRING) == false)
    {
        ei_printf("ERR: Errors in sensor list detected\r\n");
        return;
    }

    /* Init & start sensors */
    for (int i = 0; i < fusion_ix; i++)
    {
        if (sensors[fusion_sensors[i]].status == 0)
        {
            sensors[fusion_sensors[i]].status = 1; // Mark sensor as initialized
            ei_printf("%s axis sensor initialization successful.\r\n", sensors[fusion_sensors[i]].name);
        }
    }
}

/**
 * @brief      Get data and run inferencing
 */
void loop()
{
    run_Model(); // Run inferencing
}

#if !defined(EI_CLASSIFIER_SENSOR) || (EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_FUSION && EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_ACCELEROMETER)
#error "Invalid model for current sensor"
#endif

void run_Model(void)
{

    ei_printf("\nStarting inferencing in 2 seconds...\r\n");
    delay(1000);
    data_ADXL345(); // Update sensor values before running inference
    if (EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME != fusion_ix)
    {
        ei_printf("ERR: Sensors don't match the sensors required in the model\r\n"
                  "Following sensors are required: %s\r\n",
                  EI_CLASSIFIER_FUSION_AXES_STRING);
        return;
    }

    ei_printf("Sampling...\r\n");

    // Allocate a buffer here for the values we'll read from the sensor
    float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = {X_out, Y_out, Z_out};

    for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME)
    {
        // Determine the next tick (and then sleep later)
        int64_t next_tick = (int64_t)micros() + ((int64_t)EI_CLASSIFIER_INTERVAL_MS * 1000);

        for (int i = 0; i < fusion_ix; i++)
        {
            // buffer[ix + i] = *sensors[fusion_sensors[i]].value;
            // ei_printf("value: %f\n", buffer[ix + i]);
            if (sensors[fusion_sensors[i]].status == 1)
            {
                // ei_printf("Chua lay mau: %d\n", sensors[fusion_sensors[i]].status);
                sensors[fusion_sensors[i]].status = 2;
            }
            else if (sensors[fusion_sensors[i]].status == 2)
            {
                // ei_printf("Da lay mau: %d\n", sensors[fusion_sensors[i]].status);
                buffer[ix + i] = *sensors[fusion_sensors[i]].value;
                sensors[fusion_sensors[i]].status = 1; // Mark sensor as sampled
            }
        }

        int64_t wait_time = next_tick - (int64_t)micros();

        if (wait_time > 0)
        {
            delayMicroseconds(wait_time);
        }
    }

    // Turn the raw buffer into a signal which we can then classify
    signal_t signal;
    int err = numpy::signal_from_buffer(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
    if (err != 0)
    {
        ei_printf("ERR:(%d)\r\n", err);
        return;
    }

    // Run the classifier
    ei_impulse_result_t result = {0};

    err = run_classifier(&signal, &result, debug_nn);
    if (err != EI_IMPULSE_OK)
    {
        ei_printf("ERR:(%d)\r\n", err);
        return;
    }

    // Print the predictions
    ei_printf("Predictions (DSP: %d ms., Classification: %d ms., Anomaly: %d ms.):\r\n",
              result.timing.dsp, result.timing.classification, result.timing.anomaly);
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++)
    {
        ei_printf("%s: %.5f\r\n", result.classification[ix].label, result.classification[ix].value);
    }

#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("Anomaly score: %.3f\r\n", result.anomaly);

    // Check for anomaly threshold
    float anomaly_threshold = 0.5; // Set your desired anomaly threshold
    if (result.anomaly > anomaly_threshold)
    {
        ei_printf("Status: Anomaly detected!\r\n");
    }
    else
    {
        ei_printf("Status: Normal\r\n");
    }
#endif
}

/**
 * @brief Go through sensor list to find matching axis name
 */
static int8_t ei_find_axis(const char *axis_name)
{
    for (int ix = 0; ix < N_SENSORS; ix++)
    {
        if (strstr(axis_name, sensors[ix].name))
        {
            return ix;
        }
    }
    return -1;
}

/**
 * @brief Check if requested input list is valid sensor fusion, create sensor buffer
 */
static bool ei_connect_fusion_list(const char *input_list)
{
    char *buff;
    bool is_fusion = false;

    /* Copy const string in heap mem */
    char *input_string = (char *)ei_malloc(strlen(input_list) + 1);
    if (input_string == NULL)
    {
        return false;
    }
    memset(input_string, 0, strlen(input_list) + 1);
    strncpy(input_string, input_list, strlen(input_list));

    /* Clear fusion sensor list */
    memset(fusion_sensors, 0, sizeof(fusion_sensors));
    fusion_ix = 0;

    buff = strtok(input_string, "+");

    while (buff != NULL)
    { // Run through buffer
        int8_t found_axis = ei_find_axis(buff);

        if (found_axis >= 0)
        {
            if (fusion_ix < N_SENSORS)
            {
                fusion_sensors[fusion_ix++] = found_axis;
                sensors[found_axis].status = 0;
            }
            is_fusion = true;
        }

        buff = strtok(NULL, "+ ");
    }

    ei_free(input_string);

    return is_fusion;
}

/**
 * @brief Return the sign of the number
 */
float ei_get_sign(float number)
{
    return (number >= 0.0) ? 1.0 : -1.0;
}

/**
 * @brief Update ADXL345 sensor data
 */
void data_ADXL345(void)
{
    run_ADXL345();
    // Đọc dữ liệu từ cảm biến
    X_out *= CONVERT_G_TO_MS2;
    Y_out *= CONVERT_G_TO_MS2;
    Z_out *= CONVERT_G_TO_MS2;

    // Giới hạn dữ liệu để tránh nhiễu
    X_out = constrain(X_out, -MAX_ACCEPTED_RANGE * CONVERT_G_TO_MS2, MAX_ACCEPTED_RANGE * CONVERT_G_TO_MS2);
    Y_out = constrain(Y_out, -MAX_ACCEPTED_RANGE * CONVERT_G_TO_MS2, MAX_ACCEPTED_RANGE * CONVERT_G_TO_MS2);
    Z_out = constrain(Z_out, -MAX_ACCEPTED_RANGE * CONVERT_G_TO_MS2, MAX_ACCEPTED_RANGE * CONVERT_G_TO_MS2);
}


