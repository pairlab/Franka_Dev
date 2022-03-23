#include <franka/exception.h>
#include <franka/robot.h>
#include <iostream>

#include "position_controller.h"
#include <eigen3/Eigen/Core>

#include <thread>
#include <csignal>


franka::Robot robot("192.168.0.1");


void signalHandler( int signum ) {
   std::cout << "Interrupt signal (" << signum << ") received.\n";

   // cleanup and close up stuff here  
   // terminate program  

   exit(signum);  
}

void pub()
{
    int count = 0 ;
    signal(SIGINT, signalHandler);
    while(1)
    {
        std::cout<<"publishing\n";
        std::mutex g_i_mutex;
        const std::lock_guard<std::mutex> lock(g_i_mutex);
        franka::RobotState state = robot.readOnce();
        using Vector7d = Eigen::Matrix<double, 7, 1, Eigen::ColMajor>;
        Vector7d q_current = Vector7d(state.q.data());
        std::vector<double> jointBroadcast = {q_current[0], q_current[1], q_current[2], q_current[3], q_current[4], q_current[5], q_current[6]};
        joint_publisher_.writeMessage(jointBroadcast);    
    }
}



int main(int argc, char** argv) {
    std::cout<<"trying for robot connection\n";
    
    std::cout<<"got robot connection\n";
    setDefaultBehavior(robot);
    JointListener joint_listener("tcp://192.168.1.2:2069");
    //JointPublisher joint_publisher("tcp://192.168.1.3:2096");
    std::cout<<"listening to angles\n";
    //std::thread t1(pub);
    while(true) {
        std::mutex g_i_mutex;
        const std::lock_guard<std::mutex> lock(g_i_mutex);
        joint_listener.readMessage();
        std::cout<<"reading messages\n";
        auto q = joint_listener.jointAngles;



        std::array<double, 7> q_goal = {{q[0], q[1], q[2], q[3], q[4], q[5], q[6]}};
        
        std::cout << "GOAL" << std::endl;
        for(auto x: q_goal)
            std::cout << x << std::endl;
        std::cout << std::endl;

        MotionGenerator motion_generator(0.3, q_goal);
 
        robot.control(motion_generator);
    }
    //t1.join();
    std::cout<<"joining\n";
}
