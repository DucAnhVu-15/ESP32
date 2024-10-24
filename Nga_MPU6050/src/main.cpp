#include <Arduino.h>
#include <mpu6050.h>
#include <activity_tracking_inferencing.h>
#include <usart.h>

hw_timer_t *timer = NULL;
volatile uint8_t flag_status = 0;

void IRAM_ATTR onTimer()
{
  flag_status = 1;
}

typedef struct
{
  const char *name;
  float *value;
  int8_t status;
} eiSensors;

#define CONVERT_G_TO_MS2 9.80665f
#define MAX_ACCEPTED_RANGE 2.0f
#define N_SENSORS 3

float ei_get_sign(float number);
static bool ei_connect_fusion_list(const char *input_list);
static int8_t ei_find_axis(const char *axis_name);

static const bool debug_nn = false;
static float data[N_SENSORS];
static int8_t fusion_sensors[N_SENSORS];
static int fusion_ix = 0;

eiSensors sensors[] = {
    {"accX", &X_out, -1},
    {"accY", &Y_out, -1},
    {"accZ", &Z_out, -1}};

void run_Model(void);

void setup()
{
  Serial.begin(115200);

  timer = timerBegin(0, 8000, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 200, true);
  timerAlarmEnable(timer);

  setup_mpu6050();
}

void loop()
{
  if (flag_status)
  {
    flag_read_mpu6050 = 1;
    run_mpu6050();
    flag_status = 0;
  }

  if (count_data_sensor >= 300)
  {
    run_Model();
  }
}

#if !defined(EI_CLASSIFIER_SENSOR) || (EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_FUSION && EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_ACCELEROMETER)
#error "Invalid model for current sensor"
#endif

void run_Model(void)
{
  // float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = {};
  // for (int i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i++)
  // {
  //   buffer[i] = data_read[i];
  // }
  // Allocate a buffer here for the values we'll read from the sensor
  float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = {data_read[0], data_read[1], data_read[2],
                                                      data_read[3], data_read[4], data_read[5],
                                                      data_read[6], data_read[7], data_read[8],
                                                      data_read[9], data_read[10], data_read[11],
                                                      data_read[12], data_read[13], data_read[14],
                                                      data_read[15], data_read[16], data_read[17],
                                                      data_read[18], data_read[19], data_read[20],
                                                      data_read[21], data_read[22], data_read[23],
                                                      data_read[24], data_read[25], data_read[26],
                                                      data_read[27], data_read[28], data_read[29],
                                                      data_read[30], data_read[31], data_read[32],
                                                      data_read[33], data_read[34], data_read[35],
                                                      data_read[36], data_read[37], data_read[38],
                                                      data_read[39], data_read[40], data_read[41],
                                                      data_read[42], data_read[43], data_read[44],
                                                      data_read[45], data_read[46], data_read[47],
                                                      data_read[48], data_read[49], data_read[50],
                                                      data_read[51], data_read[52], data_read[53],
                                                      data_read[54], data_read[55], data_read[56],
                                                      data_read[57], data_read[58], data_read[59],
                                                      data_read[60], data_read[61], data_read[62],
                                                      data_read[63], data_read[64], data_read[65],
                                                      data_read[66], data_read[67], data_read[68],
                                                      data_read[69], data_read[70], data_read[71],
                                                      data_read[72], data_read[73], data_read[74],
                                                      data_read[75], data_read[76], data_read[77],
                                                      data_read[78], data_read[79], data_read[80],
                                                      data_read[81], data_read[82], data_read[83],
                                                      data_read[84], data_read[85], data_read[86],
                                                      data_read[87], data_read[88], data_read[89],
                                                      data_read[90], data_read[91], data_read[92],
                                                      data_read[93], data_read[94], data_read[95],
                                                      data_read[96], data_read[97], data_read[98],
                                                      data_read[99], data_read[100], data_read[101],
                                                      data_read[102], data_read[103], data_read[104],
                                                      data_read[105], data_read[106], data_read[107],
                                                      data_read[108], data_read[109], data_read[110],
                                                      data_read[111], data_read[112], data_read[113],
                                                      data_read[114], data_read[115], data_read[116],
                                                      data_read[117], data_read[118], data_read[119],
                                                      data_read[120], data_read[121], data_read[122],
                                                      data_read[123], data_read[124], data_read[125],
                                                      data_read[126], data_read[127], data_read[128],
                                                      data_read[129], data_read[130], data_read[131],
                                                      data_read[132], data_read[133], data_read[134],
                                                      data_read[135], data_read[136], data_read[137],
                                                      data_read[138], data_read[139], data_read[140],
                                                      data_read[141], data_read[142], data_read[143],
                                                      data_read[144], data_read[145], data_read[146],
                                                      data_read[147], data_read[148], data_read[149],
                                                      data_read[150], data_read[151], data_read[152],
                                                      data_read[153], data_read[154], data_read[155],
                                                      data_read[156], data_read[157], data_read[158],
                                                      data_read[159], data_read[160], data_read[161],
                                                      data_read[162], data_read[163], data_read[164],
                                                      data_read[165], data_read[166], data_read[167],
                                                      data_read[168], data_read[169], data_read[170],
                                                      data_read[171], data_read[172], data_read[173],
                                                      data_read[174], data_read[175], data_read[176],
                                                      data_read[177], data_read[178], data_read[179],
                                                      data_read[180], data_read[181], data_read[182],
                                                      data_read[183], data_read[184], data_read[185],
                                                      data_read[186], data_read[187], data_read[188],
                                                      data_read[189], data_read[190], data_read[191],
                                                      data_read[192], data_read[193], data_read[194],
                                                      data_read[195], data_read[196], data_read[197],
                                                      data_read[198], data_read[199], data_read[200],
                                                      data_read[201], data_read[202], data_read[203],
                                                      data_read[204], data_read[205], data_read[206],
                                                      data_read[207], data_read[208], data_read[209],
                                                      data_read[210], data_read[211], data_read[212],
                                                      data_read[213], data_read[214], data_read[215],
                                                      data_read[216], data_read[217], data_read[218],
                                                      data_read[219], data_read[220], data_read[221],
                                                      data_read[222], data_read[223], data_read[224],
                                                      data_read[225], data_read[226], data_read[227],
                                                      data_read[228], data_read[229], data_read[230],
                                                      data_read[231], data_read[232], data_read[233],
                                                      data_read[234], data_read[235], data_read[236],
                                                      data_read[237], data_read[238], data_read[239],
                                                      data_read[240], data_read[241], data_read[242],
                                                      data_read[243], data_read[244], data_read[245],
                                                      data_read[246], data_read[247], data_read[248],
                                                      data_read[249], data_read[250], data_read[251],
                                                      data_read[252], data_read[253], data_read[254],
                                                      data_read[255], data_read[256], data_read[257],
                                                      data_read[258], data_read[259], data_read[260],
                                                      data_read[261], data_read[262], data_read[263],
                                                      data_read[264], data_read[265], data_read[266],
                                                      data_read[267], data_read[268], data_read[269],
                                                      data_read[270], data_read[271], data_read[272],
                                                      data_read[273], data_read[274], data_read[275],
                                                      data_read[276], data_read[277], data_read[278],
                                                      data_read[279], data_read[280], data_read[281],
                                                      data_read[282], data_read[283], data_read[284],
                                                      data_read[285], data_read[286], data_read[287],
                                                      data_read[288], data_read[289], data_read[290],
                                                      data_read[291], data_read[292], data_read[293],
                                                      data_read[294], data_read[295], data_read[296],
                                                      data_read[297], data_read[298], data_read[299]};

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

  for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++)
  {
    ei_printf("%s: %.3f\r\n", result.classification[ix].label, result.classification[ix].value);

    if (result.classification[ix].value > 0.7)
    {
      ei_printf("Status: %s !\r\n", result.classification[ix].label);

      Usart_send(ix);

      continue;
    }
  }
  ei_printf("\n");
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
    int8_t found_axis = 0;

    is_fusion = false;
    found_axis = ei_find_axis(buff);

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
