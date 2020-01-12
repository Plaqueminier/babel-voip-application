#ifndef ISERVER_HPP
#define ISERVER_HPP


class Iserver
{
public:
    virtual ~Iserver() {};
    virtual void do_accept() = 0;
    virtual std::shared_ptr<Isession> create_session(tcp::socket socket, std::shared_ptr<Database> database, room &room) = 0;
};

//----------------------------------------------------------------------

#endif
