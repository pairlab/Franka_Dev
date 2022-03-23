#include "joint_listener.h"
#include <iostream>
#include <chrono>

JointListener::JointListener(std::string port) : socket_(ctx_, zmq::socket_type::sub) {
    std::cout<<"constructor\n";
    socket_.connect(port);
    socket_.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    port_ = port;
    readMessage();
}

JointListener::JointListener(const JointListener& joint_listener) : socket_(ctx_, zmq::socket_type::sub){
    std::cout<<"copy constructor\n";
    socket_.connect(joint_listener.port_);
    socket_.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    port_ = joint_listener.port_;
    readMessage();
    
}

void JointListener::readMessage() {
    auto start_1 = std::chrono::high_resolution_clock::now();
    zmq::message_t jointAnglesMessage;
    socket_.recv(&jointAnglesMessage);
    auto start_2 = std::chrono::high_resolution_clock::now();
    auto duration_1 = std::chrono::duration_cast<std::chrono::milliseconds>(start_2 - start_1);
 
    int numValues = jointAnglesMessage.size() / sizeof(double);

    for(int i = 0; i < numValues; i++)
        jointAngles.push_back(*reinterpret_cast<double*>(jointAnglesMessage.data()+i*sizeof(double)));
    auto start_3 = std::chrono::high_resolution_clock::now();
    auto duration_2 = std::chrono::duration_cast<std::chrono::milliseconds>(start_3 - start_2);

    std::cout << "duration 1 " <<  duration_1.count() << std::endl;
    std::cout << "duration 2 " <<  duration_2.count() << std::endl;
}
