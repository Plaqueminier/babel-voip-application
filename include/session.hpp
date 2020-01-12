//
//  session.hpp
//  babel_only_asio
//
//  Created by Thomas Fournier on 25/09/2019.
//
//

#ifndef session_hpp
#define session_hpp


#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "message.hpp"
#include <sstream>
#include <vector>
#include "database.hpp"
using boost::asio::ip::tcp;

//----------------------------------------------------------------------

typedef std::deque<message> message_queue;

//--------------------------------------------------------------------------------

struct User;
struct Contact;
class Database;

#include <boost/array.hpp>

class server;
class room;
class session;
// typedef boost::shared_ptr<session> std::shared_ptr<session>;

#include "Isession.hpp"

/*! \class session
 * \brief gestion de la session du client
 *
 *  Analyse et envoie les protocoles decommunication aux client
 *
 *  Liste des protocoles serveur:
 *      SIGNIN username password
 *      SIGIN SUCCESS
 *      SIGNIN FAILED
 *      LOGIN username password
 *      LOGIN SUCCESS
 *      LOGIN FAILED
 *      CALL username
 *      CALLTRANSFERT SUCCESS
 *      CALLTRANSFERT FAILED
 *      CALLREQUEST username i
 *      CALLACCEPT SUCCESS ip/username
 *      CALLACCEPT FAILED
 *      CALLSTOP USER
 *      CALLSTOP SUCCESS
 *      CALLSTOP FAILED
 *      ADDFRIEND username
 *      ADDFRIEND SUCCESS
 *      ADDFRIEND FAILED
 *      LOGOUT username
 *      LOGOUT SUCCESS
 *      LOGOUT FAILED
 *      CLIENT_CONNECT username ip
 *      CLIENT_DISCONNECT username
 *
 * En majuscule les protocoles en minuscule les arguments
 *
 *
 */

class session
  : public Isession,
    public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket socket, std::shared_ptr<Database> database, room &room);
    ~session() {
        socket_.close();
    };

    void start();
    void deliver(const char *line);

    /*!
     *  \brief Analyse et execution des protocoles
     *
     */
    void do_protocol(std::string protocol);
    void protocol_addfriend(const std::vector<std::string> &arg);
    void protocol_signin(const std::vector<std::string> &arg);
    void protocol_callstop(const std::vector<std::string> &arg);
    void protocol_calltransfer(const std::vector<std::string> &arg);
    void protocol_callaccept(const std::vector<std::string> &arg);
    void protocol_login(const std::vector<std::string> &arg);
    void protocol_logout(const std::vector<std::string> &arg);
    void protocol_test(const std::vector<std::string> &arg);
    room &get_room();
    User &get_user();
    void do_read();
    void do_write();
private:
    void handle_read(std::shared_ptr<session> &s,
                       const boost::system::error_code& ec,
                       size_t bytes_transferred);

    tcp::socket socket_;
    message read_msg_;
    message_queue write_msgs_;
    std::shared_ptr<Database> database_;
    User user_;
    room &room_;
};

//----------------------------------------------------------------------


#endif /* session_hpp */
