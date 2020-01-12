//
//  db.cpp
//  CPP_babel_2019
//
//  Created by Thomas Fournier on 30/09/2019.
//
//

#include "database.hpp"
using namespace sqlite_orm;

inline auto Database::initStorage(const std::string &path) {
    return make_storage(path,
                                make_table("users",
                                           make_column("id", &User::id, autoincrement(), primary_key()),
                                           make_column("pseudo", &User::pseudo),
                                           make_column("mdp", &User::mdp),
                                           make_column("is_connected", &User::is_connected),
                                           make_column("ip", &User::ip)

                                       ),
                                make_table("contacts",
                                    make_column("id", &Contact::id, autoincrement(), primary_key()),
                                    make_column("host", &Contact::host),
                                    make_column("connexion", &Contact::connexion),
                                    foreign_key(&Contact::host).references(&User::id).on_update.cascade(),
                                    foreign_key(&Contact::connexion).references(&User::id).on_update.cascade()
                                    )
                            );
}

using Storage = decltype(Database::initStorage(""));
static std::unique_ptr<Storage> _storage;


Database::Database()  {
    _storage =  std::make_unique<Storage>(initStorage("db.sqlite"));

    auto syncSchemaRes = _storage->sync_schema();


    for(auto &p : syncSchemaRes) {
        std::cout << p.first << " " << p.second << std::endl;
    }

    auto usrs = _storage->get_all<User>();
    for (auto usr : usrs) {
        usr.is_connected = 0;
        _storage->update(usr);
    }
    // auto test2 = _storage->get_all<User>(where(in(&User::id, _storage->select(&Contact::connexion, where(is_equal(&Contact::host, user.id))))));
    //
    // for(auto &test : test2) {
    //     std::cout << _storage->dump(test) << std::endl;
    // }

}

std::vector<User> Database::get_users_by_logs(const std::string &pseudo, const std::string &mdp )
{
    return _storage->get_all<User>(where(is_equal(&User::pseudo, pseudo) && is_equal(&User::mdp, mdp)));
}

std::vector<User> Database::get_users_by_pseudo(const std::string &pseudo)
{
    return _storage->get_all<User>(where(is_equal(&User::pseudo, pseudo)));
}

std::vector<Contact> Database::get_contacts(int host, int connexion)
{
    auto contacts = _storage->get_all<Contact>(where(is_equal(&Contact::host, host) && is_equal(&Contact::connexion, connexion)));

    for(auto &test : contacts) {
        std::cout << _storage->dump(test) << std::endl;
    }
    return contacts;

}

std::vector<User> Database::get_connected_friends(int host)
{
    return _storage->get_all<User>(where(in(&User::id, _storage->select(&Contact::connexion, where(is_equal(&Contact::host, host)))) && is_equal(&User::is_connected, 1) ));
}


// template<class T>
void Database::update(User toUpdate)
{
    _storage->update<User>(toUpdate);
}

// template<class T>
int Database::insert(User toInsert)
{
    _storage->insert<User>(toInsert);
}

// template<class T>
int Database::insert(Contact toInsert)
{
    _storage->insert<Contact>(toInsert);
}



Database::~Database() {}
