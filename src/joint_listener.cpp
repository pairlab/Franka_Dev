#include "joint_listener.h"
#include <iostream>
JointListener::JointListener(std::string port) : socket_(ctx_, zmq::socket_type::sub) {
    socket_.connect(port);
    socket_.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    port_ = port;
    readMessage();
}

JointListener::JointListener(const JointListener& joint_listener) {
    socket_.connect(joint_listener.port_);
    socket_.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    port_ = joint_listener.port_;
    readMessage();
    std::cout<<"copy constructor\n";
}

void JointListener::readMessage() {
    zmq::message_t jointAnglesMessage;
    socket_.recv(&jointAnglesMessage);
    int numValues = jointAnglesMessage.size() / sizeof(double);
    std::vector<double> jointAngles;
    for(int i = 0; i < numValues; i++)
        jointAngles.push_back(            
            *reinterpret_cast<double*>(
            jointAnglesMessage.data()+
            i*sizeof(double)));
}
