/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */
#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <ros/time.h>

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

ros::NodeHandle nh; 
std_msgs::Float32 VL53L0X_msg; 
ros::Publisher VL53L0X_distance("VL53L0X_distance", &VL53L0X_msg); 
float sensor_val; 

void setup()
{
  
  Wire.begin();
  nh.initNode(); 
  nh.advertise(VL53L0X_distance); 
  Serial.begin(57600);
  sensor.init();
  sensor.setTimeout(500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
  sensor_val = (float)sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  VL53L0X_msg.data = sensor_val; 
  VL53L0X_distance.publish(&VL53L0X_msg); 

  nh.spinOnce();
  Serial.print(sensor_val); 
  delay(2); 
  
}
