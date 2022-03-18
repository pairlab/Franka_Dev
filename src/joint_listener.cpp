#include "joint_listener.h"

JointListener::JointListener(std::string port) : socket_(ctx_, zmq::socket_type::sub) {
    socket_.connect(port);
    socket_.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    readMessage();
}

void JointListener::readMessage() {
    zmq::message_t jointAnglesMessage;
    socket_.recv(&jointAnglesMessage);
    int numValues = jointAnglesMessage.size() / sizeof(double);
    std::vector<double> jointAngles;
    for(int i = 0; i < numValues; i++)
        jointAngles.push_back(*reinterpret_cast<double*>(jointAnglesMessage.data()+i*sizeof(double)));
}
