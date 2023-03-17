#ifndef MDBHANDLER_H
#define MDBHANDLER_H

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/client_session.hpp>
#include <mongocxx/exception/query_exception.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

#include "Account.h"
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

class MDBHandler
{
public:
    MDBHandler();
    ~MDBHandler();

    mongocxx::instance inst{};

    bool testConnection();
    int Menu();
private:
    std::string account;
    std::string password;
    std::string uri_string;
    mongocxx::uri uri;
    mongocxx::client conn;
    mongocxx::database db;
    mongocxx::collection coll;

    void countUsers();
    void createAccount();
    void ModifyExistingAccount();

protected:
};


#endif