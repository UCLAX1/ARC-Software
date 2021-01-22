#include <webots/connector.h>
#include <webots/position_sensor.h>
#include <webots/robot.h>

#define TIME_STEP 64

int main() {
  WbDeviceTag connector;

  wb_robot_init();

  // get a handler to the connector, the motor and the position_sensor.
  connector = wb_robot_get_device("connector");

  // activate it
  wb_connector_enable_presence(connector, TIME_STEP);
  
  while (wb_robot_step(TIME_STEP) != -1) {}
  
  wb_robot_cleanup();
  return 0;  // EXIT_SUCCESS
}