#include <string>

class GateIP {
public:
    explicit GateIP(std::string ip) : ip_(std::move(ip)) {}

    const std::string & get_ip() const {
        return ip_;
    }
    
    void set_ip(const std::string &new_ip) {
        ip_ = new_ip;
    }

private:
    std::string ip_;
};