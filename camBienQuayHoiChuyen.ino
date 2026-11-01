#include "MPU6050.h"
MPU6050 sensor;

int gx, gy, gz;

void setup(){
  Serial.begin(115200);
  Wire.begin();

  sensor.initialize();

  if(sensor.testConnection()){
    Serial.println("Init MPU6050 ok");
  } else {
    Serial.println("Init MPU6050 error");
    while(1);
  }
}

void loop(){
  sensor.getRotation(&gx, &gy, &gz);

  Serial.print("g[x y z]:\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz); 

  delay(3000);
}