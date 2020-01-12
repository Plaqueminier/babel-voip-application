//
//  session.hpp
//  babel_only_asio
//
//  Created by Thomas Fournier on 25/09/2019.
//
//

#ifndef Isession_hpp
#define Isession_hpp

class User;

class Isession {
public:
    virtual ~Isession() {};
    virtual void start() = 0;
    virtual void deliver(const char *line)  = 0;

    virtual void do_protocol(std::string protocol) = 0;
    virtual void protocol_addfriend(const std::vector<std::string> &arg) = 0;
    virtual void protocol_signin(const std::vector<std::string> &arg) = 0;
    virtual void protocol_callstop(const std::vector<std::string> &arg) = 0;
    virtual void protocol_calltransfer(const std::vector<std::string> &arg) = 0;
    virtual void protocol_callaccept(const std::vector<std::string> &arg) = 0;
    virtual void protocol_login(const std::vector<std::string> &arg) = 0;
    virtual void protocol_logout(const std::vector<std::string> &arg) = 0;
    virtual void protocol_test(const std::vector<std::string> &arg) = 0;
    virtual room &get_room() = 0;
    virtual User &get_user() = 0;
    virtual void do_read() = 0;
    virtual void do_write() = 0;
};

//----------------------------------------------------------------------


#endif /* Isession_hpp */
