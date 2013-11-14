#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
  
  // Calibration values. Use the Calibrate example program to get the values for
  // your compass.
  compass.m_min.x = -32768; compass.m_min.y = -32768; compass.m_min.z = -32768;
  compass.m_max.x = +32767; compass.m_max.y = +32767; compass.m_max.z = +32767;
}

void loop() {
  compass.read();
  float heading = compass.heading((LSM303::vector<int>){0,-1,0});
  Serial.println(heading);
  delay(100);
}