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
  iter = 25;

  while (wb_robot_step(TIME_STEP) != -1) {

    if (wb_connector_get_presence(connector) == 1) {
      return -1;
      //wb_connector_lock(connector);
    }
    if (wb_connector_get_presence(connector) == -1) {
      return -1;
    }
        
    /*switch (state) {
      // Projectile attached to magnetic ceiling
      case CONNECTOR_IN_PLACE:
        if (iter >= 25) {
          state = INACTIVE;
          iter = 0;  
        }
        else {
          iter++;
        }
        break;

      // Projectile launching, ready to connect
      case CONNECTING:
        if (wb_connector_get_presence(connector) == 1) {
          wb_connector_lock(connector);
          state = CONNECTOR_IN_PLACE;
        }
        break;

      // wait for the motor to be in the new place (hopping).
      case INACTIVE:
        if (iter >= 75) {
          state = CONNECTING;
          iter = 0;  
        }
        else {
          iter++;
        }
        break;
      }*/
    
  }
  wb_robot_cleanup();
  return 0;  // EXIT_SUCCESS
}