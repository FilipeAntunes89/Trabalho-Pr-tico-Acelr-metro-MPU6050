#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int16_t accel[3], gyro[3];
float ref[3] = {0, 0, 0};
float gain[3] = {0, 0, 0};
float offset[3] = {0, 0, 0};
float output[3] = {0, 0, 0};
float angle = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
}

void loop() {
  mpu.getMotion6(&accel[0], &accel[1], &accel[2], &gyro[0], &gyro[1], &gyro[2]);

  float Ax_P = 1.04, Ax_N = -0.94;
  float Ay_P = 0.99, Ay_N = -0.99;
  float Az_P = 1.06, Az_N = -0.97;

  for(int i=0; i<3; i++) {
    ref[i] = accel[i]/16384.0;
    gain[i] = ((i==0?Ax_P:(i==1?Ay_P:Az_P)) - (i==0?Ax_N:(i==1?Ay_N:Az_N)))/2 ;
    offset[i] = ((i==0?Ax_P:(i==1?Ay_P:Az_P)) + (i==0?Ax_N:(i==1?Ay_N:Az_N)))/2 ;
    output[i] = (gain[i] * ref[i]) + offset[i];
  }

  Serial.println("Inicializando o sistema, posicione o sensor....");
  Serial.println("Ganhos : " + String(gain[0]) + ", " + String(gain[1]) + ", " + String(gain[2]));
  Serial.println("Offsets : " + String(offset[0]) + ", " + String(offset[1]) + ", " + String(offset[2]));
  Serial.println("Saídas com compensação : " + String(output[0]) + ", " + String(output[1]) + ", " + String(output[2]));
  Serial.println("Saídas sem compensação : " + String(ref[0]) + ", " + String(ref[1]) + ", " + String(ref[2]));

  delay(5000);

  angle = atan( output[1] / sqrt(pow(output[0], 2) + pow(output[2], 2))) * 180/M_PI;
}
