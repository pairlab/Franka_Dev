#pragma once

#include <array>
#include <string>

#include <eigen3/Eigen/Core>

#include <franka/control_types.h>
#include <franka/duration.h>
#include <franka/robot.h>
#include <franka/robot_state.h>

#include "joint_listener.h"
#include "joint_publisher.h"

#include <memory>

#define DOF 7 

namespace torqueComms {
    extern JointListener jointListener;
    extern JointPublisher jointPublisher;
}

class TorqueGenerator {
public:
    TorqueGenerator(franka::Robot& robot);

    franka::Torques operator()(const franka::RobotState& robot_state, franka::Duration period);

private:
    // stiffness
    const std::array<double, DOF> k_s = {{600.0, 600.0, 600.0, 600.0, 250.0, 150.0, 50.0}};
    // damping
    const std::array<double, DOF> k_d = {{50.0, 50.0, 50.0, 50.0, 30.0, 25.0, 15.0}};
    // dynamics/kinematics model
    franka::Model model;
    // count for receiving data 
    size_t count;
    // desired joint configuration
    std::vector<double> q_goal;
};