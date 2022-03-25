#include <franka/exception.h>
#include <franka/robot.h>
#include <iostream>

#include "torque_controller.h"
#include "position_controller_og.h"

int main(int argc, char** argv) {
    try {
        franka::Robot robot("192.168.0.1");
        setDefaultBehavior(robot);
        TorqueGenerator torqueController(robot);
        
        while(true) {
            robot.control(torqueController);
        }

    } catch (const franka::Exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
}