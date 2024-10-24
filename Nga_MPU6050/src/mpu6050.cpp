#include <mpu6050.h>

Adafruit_MPU6050 mpu;
float X_out = 0;
float Y_out = 0;
float Z_out = 0;
uint8_t flag_read_mpu6050 = 0;
float data_read[300] = {0};
uint16_t count_data_sensor = 0;

void setup_mpu6050(void)
{
    mpu.begin();
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

    mpu.setGyroRange(MPU6050_RANGE_1000_DEG);

    mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);
}

void run_mpu6050(void)
{

    if (flag_read_mpu6050)
    {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        X_out = a.acceleration.x;
        Y_out = a.acceleration.y;
        Z_out = a.acceleration.z;

        if (count_data_sensor + 2 < 300)
        {
            data_read[count_data_sensor] = X_out;
            data_read[count_data_sensor + 1] = Y_out;
            data_read[count_data_sensor + 2] = Z_out;

            count_data_sensor += 3;
        }
        else
        {
            count_data_sensor = 0;
        }

        flag_read_mpu6050 = 0;
    }
}
