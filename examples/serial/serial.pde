#include <Wire.h>
#include <LSM303DLH.h>

LSM303DLH compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass.enable();
}

void loop() {
  compass.read();

  Serial.print("A ");
  Serial.print("X: ");
  Serial.print(compass.accelerometerX);
  Serial.print(" Y: ");
  Serial.print(compass.accelerometerY);
  Serial.print(" Z: ");
  Serial.print(compass.accelerometerZ);

  Serial.print(" M ");  
  Serial.print("X: ");
  Serial.print(compass.magnetometerX);
  Serial.print(" Y: ");
  Serial.print(compass.magnetometerY);
  Serial.print(" Z: ");
  Serial.println(compass.magnetometerZ);
}