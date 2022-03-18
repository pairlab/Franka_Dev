#include <zmq.hpp>
#include <vector>

class JointListener {
private:
    zmq::context_t ctx_;
    zmq::socket_t socket_;
    bool messageChanged_;


public:
    JointListener(std::string port);
    void readMessage();

    std::vector<double> jointAngles;
    
};
