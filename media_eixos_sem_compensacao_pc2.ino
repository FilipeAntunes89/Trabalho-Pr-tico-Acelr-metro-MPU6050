#include <Wire.h>
#include <MPU6050.h>

MPU6050 sensor;

const int sampleCount = 100;
int16_t xAccel, yAccel, zAccel;
int16_t xGyro, yGyro, zGyro;

int32_t xAccelSum = 0, yAccelSum = 0, zAccelSum = 0;
int32_t xGyroSum = 0, yGyroSum = 0, zGyroSum = 0;

float xAccel_N = 0, yAccel_N = 0, zAccel_N = 0;
float xAccel_P = 0, yAccel_P = 0, zAccel_P = 0;

void setup() {
 Serial.begin(9600);

 Wire.begin();
 sensor.initialize();
}

void loop() {
 Serial.println("Coletando medidas de acerelacao no eixo X positivo, posicione o sensor");
 delay(20000);
 Serial.println("Iniciando medicao do eixo +X");

 for (int i = 0; i < sampleCount; i++) {
   sensor.getMotion6(&xAccel, &yAccel, &zAccel, &xGyro, &yGyro, &zGyro);

   Serial.println("Accel +X: " + String(xAccel/16384.0));
   xAccel_P += xAccel/16384.0;
   delay(10);
 }
 
 xAccel_P = xAccel_P/100 ;

 Serial.println("Coletando medidas de acerelacao no eixo X negativo, posicione o sensor");
 delay(20000);
 Serial.println("Iniciando medicao do eixo -X");
 
 for (int i = 0; i < sampleCount; i++) {
   sensor.getMotion6(&xAccel, &yAccel, &zAccel, &xGyro, &yGyro, &zGyro);
   Serial.println("Accel -X: " + String(xAccel/16384.0));
   xAccel_N += xAccel/16384.0;
   delay(10);
 }
 
 xAccel_N = xAccel_N/100 ;

 Serial.println("Coletando medidas de acerelacao no eixo Y positivo, posicione o sensor");
 delay(20000);
 Serial.println("Iniciando medicao do eixo +Y");
 
 for (int i = 0; i < sampleCount; i++) {
   sensor.getMotion6(&xAccel, &yAccel, &zAccel, &xGyro, &yGyro, &zGyro);
   Serial.println("Accel +Y: " + String(yAccel/16384.0));
   yAccel_P += yAccel/16384.0;
   delay(10);
 }
 yAccel_P = yAccel_P/100 ;

 Serial.println("Coletando medidas de acerelacao no eixo Y negativo, posicione o sensor");
 delay(20000);
 Serial.println("Iniciando medicao do eixo -Y");
 
 for (int i = 0; i < sampleCount; i++) {
   sensor.getMotion6(&xAccel, &yAccel, &zAccel, &xGyro, &yGyro, &zGyro);
   Serial.println("Accel -Y: " + String(yAccel/16384.0));
   yAccel_N += yAccel/16384.0;
   delay(10);
 }
 yAccel_N = yAccel_N/100 ;

 Serial.println("Coletando medidas de acerelacao no eixo Z positivo, posicione o sensor");
 delay(20000);
 Serial.println("Iniciando medicao do eixo +Z");
 
 for (int i = 0; i < sampleCount; i++) {
   sensor.getMotion6(&xAccel, &yAccel, &zAccel, &xGyro, &yGyro, &zGyro);
   Serial.println("Accel +Z: " + String(zAccel/16384.0));
   zAccel_P += zAccel/16384.0;
   delay(10);
 }
 zAccel_P = zAccel_P/100 ;

 Serial.println("Coletando medidas de acerelacao no eixo Z negativo, posicione o sensor");
 delay(20000);
 Serial.println("Iniciando medicao do eixo -Z");
 
 for (int i = 0; i < sampleCount; i++) {
   sensor.getMotion6(&xAccel, &yAccel, &zAccel, &xGyro, &yGyro, &zGyro);
   Serial.println("Accel -Z: " + String(zAccel/16384.0));
   zAccel_N += zAccel/16384.0;
   delay(10);
 }
 zAccel_N = zAccel_N/100 ;

 Serial.println("Acelaracao media em +X: " + String(xAccel_P));
 Serial.println("Acelaracao media em -X: " + String(xAccel_N));
 Serial.println("Acelaracao media em +Y: " + String(yAccel_P));
 Serial.println("Acelaracao media em -Y: " + String(yAccel_N));
 Serial.println("Acelaracao media em +Z: " + String(zAccel_P));
 Serial.println("Acelaracao media em -Z: " + String(zAccel_N));

 while (true) {
 ;
 }
}

