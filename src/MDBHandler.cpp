#include "MDBHandler.h"

MDBHandler::MDBHandler()
{
}

MDBHandler::~MDBHandler()
{
}

bool MDBHandler::testConnection()
{

    std::cout << "Enter DB account: ";
    std::cin >> account;
    std::cout << "Enter DB password: ";
    std::cin >> password;
    uri_string = "mongodb+srv://" + account + ":" + password + "@cluster0.vyxv6f7.mongodb.net/test";
    uri = mongocxx::uri{uri_string};
    conn = mongocxx::client{uri};
    db = conn.database("Bank");
    coll = db.collection("Users");
    try
    {
        auto server_status = conn["admin"].run_command(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1)));
        std::cout << "Connection successful!" << std::endl;
        return true;
    }
    catch (const mongocxx::exception &e)
    {
        std::cout << e.what() << '\n';
        return false;
    }
}

int MDBHandler::Menu()
{
    int x;
    std::cout << "Menu Options:\n";
    std::cout << "1. Number of accounts\n";
    std::cout << "2. Create account\n";
    std::cout << "3. Modify an existing account\n";
    std::cout << "4. Delete account\n";
    std::cout << "5. Add money to an account\n";
    std::cout << "5. Search account\n";
    std::cout << "6. Exit\n";
    std::cout << "Type corespunding number to make a procedure: ";
    int input;
    std::cin >> input;
    switch (input)
    {
    case 1:
        countUsers();
        break;

    default:
        break;
    }

    return x;
}

void MDBHandler::countUsers()
{
    std::cout << coll.count_documents({}) << std::endl;
}

void MDBHandler::createAccount()
{
    /*auto builder = document{};
    bsoncxx::document::value docValue = builder << "Name"<<
                                                << "Surname"
                                                << "PhoneNumber"
                                                << "IBAN"
                                                << "Sold" << bsoncxx::builder::stream::close_document
                                                << bsoncxx::builder::stream::finalize; */
}
