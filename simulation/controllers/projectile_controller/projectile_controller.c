#include <webots/connector.h>
#include <webots/position_sensor.h>
#include <webots/robot.h>

#define SPEED 2
#define TIME_STEP 64

typedef enum { CONNECTOR_IN_PLACE, CONNECTING, INACTIVE } states;

int main() {
  WbDeviceTag connector;
  
  states state;
  int iter;

  wb_robot_init();

  // get a handler to the connector, the motor and the position_sensor.
  connector = wb_robot_get_device("connector");

  // activate it
  wb_connector_enable_presence(connector, TIME_STEP);
  
  state = INACTIVE;
  iter = 0;

  while (wb_robot_step(TIME_STEP) != -1) {

    if (state == INACTIVE && wb_connector_get_presence(connector) == 1) {
      wb_connector_lock(connector);
      state = CONNECTOR_IN_PLACE;
      iter = 0;
    }
    
    if (state == CONNECTOR_IN_PLACE && iter >= 100) {
      wb_connector_unlock(connector);
      state = INACTIVE;
    }
        
    iter++;    
  }
  wb_robot_cleanup();
  return 0;  // EXIT_SUCCESS
}