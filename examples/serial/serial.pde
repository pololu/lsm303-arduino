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
  Serial.print(compass.a.x);
  Serial.print(" Y: ");
  Serial.print(compass.a.y);
  Serial.print(" Z: ");
  Serial.print(compass.a.z);

  Serial.print(" M ");  
  Serial.print("X: ");
  Serial.print(compass.m.x);
  Serial.print(" Y: ");
  Serial.print(compass.m.y);
  Serial.print(" Z: ");
  Serial.println(compass.m.z);
  
  delay(100);
}