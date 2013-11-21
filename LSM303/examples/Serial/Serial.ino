#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

char report[80];

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
}

void loop()
{
  compass.read();

  snprintf(report, sizeof(report), "%8d%8d%8d%8d%8d%8d",
    compass.a.x, compass.a.y, compass.a.z,
    compass.m.x, compass.m.y, compass.m.z);
  Serial.println(report); 
  
  delay(100);
}