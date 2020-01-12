//
//  db.hpp
//  CPP_babel_2019
//
//  Created by Thomas Fournier on 30/09/2019.
//
//

#ifndef database_hpp
#define database_hpp

#include <stdio.h>
#include <sqlite_orm/sqlite_orm.h>
#include <iostream>


struct User{
    int id;
    std::string pseudo;
    std::string mdp;
    bool is_connected;
    std::string ip;

};

struct Contact
{
    int id;
    int host;
    int connexion;
};


class Database
: public std::enable_shared_from_this<Database>

{
private:
public:

    static inline auto initStorage(const std::string &path);

    std::vector<User> get_users_by_logs(const std::string &pseudo, const std::string &mdp);
    std::vector<User> get_users_by_pseudo(const std::string &pseudo);
    std::vector<Contact> get_contacts(int host, int connexion);
    std::vector<User> get_connected_friends(int host);


    void update(User toUpdate);
    int insert(User toInserte);
    int insert(Contact toInserte);


    Database();
    ~Database();
protected:

};


#endif /* database_hpp */
