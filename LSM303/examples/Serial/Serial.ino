#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
}

void loop() {
  compass.read();

  Serial.print("A ");
  Serial.print("X: ");
  Serial.print((int)compass.a.x);
  Serial.print(" Y: ");
  Serial.print((int)compass.a.y);
  Serial.print(" Z: ");
  Serial.print((int)compass.a.z);

  Serial.print(" M ");  
  Serial.print("X: ");
  Serial.print((int)compass.m.x);
  Serial.print(" Y: ");
  Serial.print((int)compass.m.y);
  Serial.print(" Z: ");
  Serial.println((int)compass.m.z);
  
  delay(100);
}