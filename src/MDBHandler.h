#ifndef MDBHANDLER_H
#define MDBHANDLER_H

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <mongocxx/cursor.hpp>
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
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;
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
    int MainMenu();

private:
    
    std::string uri_string;
    mongocxx::uri uri;
    mongocxx::client conn;
    mongocxx::database db;
    mongocxx::collection coll;

    std::string SearchCrtMenu();
    std::string SetMenu();

    void countUsers();
    void createAccount();
    void ModifyExistingAccount();

    void printOneDocument(mongocxx::stdx::optional<bsoncxx::document::value> &document);

    void printAllDoccuments();
    /// @brief print document with
    /// @param document
    void printDocument(bsoncxx::v_noabi::document::view &document);
    bsoncxx::document::view_or_value filterSearch();
    void updateOneDocument(bsoncxx::document::view_or_value filterSearch);

    void searchAccount();

    void pause();

protected:
};

#endif