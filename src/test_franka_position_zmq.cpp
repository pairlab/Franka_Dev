#include <franka/exception.h>
#include <franka/robot.h>
#include <iostream>

#include "position_controller.h"

int main(int argc, char** argv) {
    franka::Robot robot("192.168.0.1");
    setDefaultBehavior(robot);
    JointListener joint_listener("PASS IN IP ADDRESS!");

    while(true) {
        joint_listener.readMessage();
        auto q = joint_listener.jointAngles;
        std::array<double, 7> q_goal = {{q[0], q[1], q[2], q[3], q[4], q[5], q[6]}};

        MotionGenerator motion_generator(0.3, q_goal);

        robot.control(motion_generator);
    }
}
