#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int numSamples = 100;
int16_t accelX, accelY, accelZ;
int16_t gyroX, gyroY, gyroZ;

// Variáveis de calibração dinâmicas
float accelX_P = 1.04;  // Média obtida durante calibração
float accelX_N = -0.94; // Média obtida durante calibração
float accelY_P = 1.01;  // Média obtida durante calibração
float accelY_N = -0.98; // Média obtida durante calibração
float accelZ_P = 1.06;  // Média obtida durante calibração
float accelZ_N = -0.97; // Média obtida durante calibração

// Variáveis para o ganho
float ganhox, ganhoy, ganhoz = 0;

// Variáveis para o Aoffset
float Aoffsetx, Aoffsety, Aoffsetz = 0;

// Variáveis para a saída real
float saida_x, saida_y, saida_z = 0;

// Variável para o ângulo
float angulo = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
}

void loop() {
  Serial.println("Posicione o sensor em 0 graus e aguarde 5 segundos...");
  delay(5000);
  coletarDados();

  Serial.println("Posicione o sensor em 45 graus e aguarde 5 segundos...");
  delay(5000);
  coletarDados();

  Serial.println("Posicione o sensor em 90 graus e aguarde 5 segundos...");
  delay(5000);
  coletarDados();
}

void coletarDados() {
  float accel_ref_X, accel_ref_Y, accel_ref_Z;

  for (int i = 0; i < numSamples; ++i) {
    // Medindo médias
    mpu.getMotion6(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);

    // Obtendo o valor de medida de referência
    accel_ref_X = accelX / 16384.0;
    accel_ref_Y = accelY / 16384.0;
    accel_ref_Z = accelZ / 16384.0;

    // Cálculo do ganho para cada eixo
    ganhox = (accelX_P - accelX_N) / 2;
    ganhoy = (accelY_P - accelY_N) / 2;
    ganhoz = (accelZ_P - accelZ_N) / 2;

    // Cálculo do Aoffset para cada eixo
    Aoffsetx = (accelX_P + accelX_N) / 2;
    Aoffsety = (accelY_P + accelY_N) / 2;
    Aoffsetz = (accelZ_P + accelZ_N) / 2;

    // Cálculo da saída real
    saida_x = (ganhox * (accel_ref_X - Aoffsetx)) + Aoffsetx;
    saida_y = (ganhoy * (accel_ref_Y - Aoffsety)) + Aoffsety;
    saida_z = (ganhoz * (accel_ref_Z - Aoffsetz)) + Aoffsetz;

    // Cálculo do ângulo utilizando X como eixo de rotação com compensação angular
    angulo = atan2(saida_y, saida_z) * 180.0 / PI;

    // Ajuste do ângulo para o intervalo de 0 a 360 graus
    angulo = fmod(angulo + 360, 360);

    Serial.println("Ângulo: " + String(angulo));
  }
}
