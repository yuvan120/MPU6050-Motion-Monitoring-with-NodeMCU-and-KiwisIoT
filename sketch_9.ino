#include <KiwisIoT.h>
#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

const char* ssid = "wifi name";
const char* pass = "password";
const char* topic = "dash_1791296287923";

KiwisIoT kiwisiot(ssid, pass, topic);

MPU6050 mpu;

void setup() {

  Serial.begin(115200);
  delay(1000);

  // MPU6050
  // SDA -> D2
  // SCL -> D1
  Wire.begin(D2, D1);

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 Connected Successfully");
  } else {
    Serial.println("MPU6050 Connection Failed");
  }

  // Start KiwisIoT
  kiwisiot.begin();

  Serial.println("MPU6050 + KiwisIoT Started");
}

void loop() {

  // Keep KiwisIoT connection running
  kiwisiot.run();

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // Read MPU6050
  mpu.getMotion6(
    &ax, &ay, &az,
    &gx, &gy, &gz
  );

  // Combine X, Y and Z into ONE balance angle
  float balanceAngle = atan2(
    sqrt(
      (float)ax * ax +
      (float)ay * ay
    ),
    (float)az
  ) * 180.0 / PI;

  // Serial Monitor
  Serial.print("X: ");
  Serial.print(ax);

  Serial.print(" | Y: ");
  Serial.print(ay);

  Serial.print(" | Z: ");
  Serial.print(az);

  Serial.print(" | Balance Angle: ");
  Serial.print(balanceAngle, 2);

  Serial.println(" degree");
kiwisiot.send ("1",balanceAngle);

  // ==================================
  // KiwisIoT CHANNEL 1
  // ==================================

  // Send balanceAngle to Channel 1 here
  // Use your KiwisIoT library's actual
  // Channel publish function.

  delay(2000);
}