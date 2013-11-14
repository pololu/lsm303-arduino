#include <Wire.h>
#include <LSM303.h>

LSM303 compass;
LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768};

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
}

void loop() {  
  compass.read();
  
  running_min.x = min(running_min.x, compass.m.x);
  running_min.y = min(running_min.y, compass.m.y);
  running_min.z = min(running_min.z, compass.m.z);

  running_max.x = max(running_max.x, compass.m.x);
  running_max.y = max(running_max.y, compass.m.y);
  running_max.z = max(running_max.z, compass.m.z);
  
  Serial.print("M min ");
  Serial.print("X: ");
  Serial.print((int)running_min.x);
  Serial.print(" Y: ");
  Serial.print((int)running_min.y);
  Serial.print(" Z: ");
  Serial.print((int)running_min.z);

  Serial.print(" M max ");  
  Serial.print("X: ");
  Serial.print((int)running_max.x);
  Serial.print(" Y: ");
  Serial.print((int)running_max.y);
  Serial.print(" Z: ");
  Serial.println((int)running_max.z);
  
  delay(100);
}