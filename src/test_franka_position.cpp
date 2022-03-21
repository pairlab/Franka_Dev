#include <franka/exception.h>
#include <franka/robot.h>
#include <iostream>

#include "position_controller_og.h"

// int main(int argc, char** argv) {
//     try {
//         franka::Robot robot("192.168.0.1");
        
//         setDefaultBehavior(robot);
//         std::array<double, 7> q_goal = {{0, -M_PI_4, 0, -3 * M_PI_4, 0, M_PI_2, M_PI_4}};
//         std::cout << "starting" << std::endl;
//         MotionGeneratorOg motion_generator(0.3, q_goal);  
//     	robot.control(motion_generator);
// 	    std::cout << "finished" << std::endl;

//         } catch (const franka::Exception& e) {
//         std::cout << e.what() << std::endl;
//         return -1;
//     }
// }



/*

    while(true) {
        auto q_goal = joint_listener.receive();
        MotionGeneratorOg motion_Generator(q_goal)
        robot.control(motion_generator)
    }
*/