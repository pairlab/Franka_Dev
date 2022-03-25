#include "torque_controller.h"

#include <algorithm>
#include <array>
#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>

#include <franka/exception.h>
#include <franka/robot.h>

namespace torqueComms {
    JointListener jointListener("tcp://192.168.1.2:2069");
    JointPublisher jointPublisher("tcp://192.168.1.3:2096");
}

TorqueGenerator::TorqueGenerator(franka::Robot& robot) {
    model = robot.loadModel();
    count = 0;
}

franka::Torques TorqueGenerator::operator()(const franka::RobotState& robot_state,
                                                   franka::Duration period) {
    // coriolis compensation

    if(count % 20 == 0) {
        torqueComms::jointListener.readMessage();
        q_goal = torqueComms::jointListener.jointAngles;
    }
    count++;
    // read current coriolis terms from model
    std::array<double, DOF> coriolis = model.coriolis(robot_state);
    // read gravity term from model (maybe we might want this?)
    // std::array<double, DOF> gravity = model.gravity(state);
    std::array<double, DOF> tau_d_calculated;
    for (size_t i = 0; i < DOF; i++) {
        tau_d_calculated[i] =
            k_gains[i] * (q_goal[i] - robot_state.q[i]) 
            - d_gains[i] * robot_state.dq[i] 
            + coriolis[i];
    }

    // publish joint states
    std::vector<double> jointBroadcast = {
        robot_state.q[0], robot_state.q[1], robot_state.q[2], robot_state.q[3], 
        robot_state.q[4], robot_state.q[5], robot_state.q[6]};
    torqueComms::jointPublisher.writeMessage(jointBroadcast);

    return tau_d_calculated;
}