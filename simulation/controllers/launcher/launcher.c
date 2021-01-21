#include <webots/distance_sensor.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <stdio.h>

#define TIME_STEP 64

int main(int argc, char **argv) {
  wb_robot_init();
  
  int iter = 0;
  int falling = 0;
  
  WbDeviceTag pusher;
  pusher = wb_robot_get_device("slide_motor");
  //wb_motor_set_position(pusher, 0);
  //wb_motor_set_velocity(pusher, .01);
  
  // Behavior loop
  while (wb_robot_step(TIME_STEP) != -1) {
    /*double left_speed = 1.0;
    double right_speed = 1.0;
    double ds_values[2];
    
    // Avoid obstacle
    if (avoid_obstacle == 1) {
      read_sensors(ds, ds_values, 2);
      
      if (ds_values[0] < 950.0 || ds_values[1] < 950.0) {
        left_speed = 1.0;
        right_speed = -1.0;
      }
      else {
        avoid_obstacle = 0;
      }  
    } 
    else { // read sensors
      read_sensors(ds, ds_values, 2);
      
      printf("Left:  %f  |  Right  %f", ds_values[0], ds_values[1]);  
      
      // Change to avoid state if obstacle is near
      if (ds_values[0] < 950.0 || ds_values[1] < 950.0) {
        avoid_obstacle = 1;
      }
    }*/
    if (iter % 50 == 0) {
      falling = !falling;
    }
    if (falling == 0) {
      wb_motor_set_force(pusher, -15);
    }
    else {
      wb_motor_set_force(pusher, 0);
    }
    iter++;
    
    
    printf("Iter = %d", iter);
    fflush(stdout);
    //wb_motor_set_velocity(wheels[1], right_speed);
    //wb_motor_set_velocity(wheels[2], left_speed);
    //wb_motor_set_velocity(wheels[3], right_speed);
  }
  wb_robot_cleanup();
  return 0;  // EXIT_SUCCESS
}