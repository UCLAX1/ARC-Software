#include <webots/connector.h>
#include <webots/distance_sensor.h>
#include <webots/motor.h>
#include <webots/position_sensor.h>
#include <webots/robot.h>
#include <stdio.h>

#define TIME_STEP 64

typedef enum { INACTIVE, LOADING, CONNECTING, CLIMBING } states;

int main(int argc, char **argv) {
  wb_robot_init();
  
  states state = CONNECTING;
  int iter = 0;
  
  // Enable spring motor
  WbDeviceTag spring_motor;
  spring_motor = wb_robot_get_device("spring_motor");
  
  // Enable tether motor
  WbDeviceTag tether_motor;
  tether_motor = wb_robot_get_device("tether_motor");
  
  // Enable magnet
  WbDeviceTag connector;
  connector = wb_robot_get_device("connector");
  wb_connector_enable_presence(connector, TIME_STEP);
  
  // Behavior loop
  while (wb_robot_step(TIME_STEP) != -1) {
    
    switch(state) {
      case INACTIVE:
        wb_motor_set_force(spring_motor, 0);
        wb_motor_set_force(tether_motor, 0);
        
        if (iter >= 50) {
          state = LOADING;
          iter = 0;
        }
        break;
        
      case LOADING:
        wb_motor_set_force(spring_motor, -15);
        wb_motor_set_force(tether_motor, 0);
        
        if (iter >= 50) {
          state = CONNECTING;
          iter = 0;
        }
        break;
          
      case CONNECTING:
        wb_motor_set_force(spring_motor, 0);
        wb_motor_set_force(tether_motor, 0);
        
        if (wb_connector_get_presence(connector) == 1) {
          wb_connector_lock(connector);
        }
        
        if (iter >= 50) {
          state = CLIMBING;
          iter = 0;
        }
        break;
        
      case CLIMBING:
        wb_motor_set_force(spring_motor, 0);
        wb_motor_set_position(tether_motor, 0.15);
        
         if (iter >= 50) {
          state = CLIMBING;
          iter = 0;
          //wb_connector_unlock(connector);
        }
    }
            
    iter++;
    
  }
  wb_robot_cleanup();
  return 0;  // EXIT_SUCCESS
}