#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;

char command = 'S'; // Default Stop

void setup() {
  Serial.begin(9600);   // Bluetooth TX
  Wire.begin();
  mpu.initialize();
}

void loop() {
  mpu.getAcceleration(&ax, &ay, &az);

  // Gesture detection (adjust values if needed)
  if (ay < -10000) {
    command = 'F';  // Forward
  }
  else if (ay > 10000) {
    command = 'B';  // Backward
  }
  else if (ax > 10000) {
    command = 'R';  // Right
  }
  else if (ax < -10000) {
    command = 'L';  // Left
  }
  else {
    command = 'S';  // Stop
  }

  Serial.write(command); // Send via Bluetooth
  delay(200);
}
