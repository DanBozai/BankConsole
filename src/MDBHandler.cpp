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
    std::cout << "Type corresponding number to initiate a procedure:: ";
    int input;
    std::cin >> input;
    switch (input)
    {
    case 1:
        countUsers();
        break;
    case 2:
        createAccount();
        break;
    case 3:
        ModifyExistingAccount();
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
    Account *UserAccount = new Account();

    auto builder = document{};
    bsoncxx::document::value docValue = builder << "Name" << UserAccount->getName()
                                                << "Surname" << UserAccount->getSurname()
                                                << "PhoneNumber" << UserAccount->getPhoneNumber()
                                                << "IBAN" << UserAccount->getIBAN()
                                                << "Sold" << UserAccount->getSold()
                                                << bsoncxx::builder::stream::finalize;

    coll.insert_one({docValue});
    delete UserAccount;
}

void MDBHandler::ModifyExistingAccount()
{
    std::string searchCrt = "";
    std::string inputName="";
    std::cout << "Type username to search: ";
    std::cin >> searchCrt;
    

    std::cout<<"Type the value you want to change for Name: ";
    std::cin>>inputName;
    auto builder = document{};
    

    bsoncxx::document::view_or_value searchFilter = builder << "Name" << searchCrt << bsoncxx::builder::stream::finalize;

    bsoncxx::document::view_or_value updateData = builder << "$set" << bsoncxx::builder::stream::open_document
                                                          << "Name"
                                                          << inputName
                                                          << bsoncxx::builder::stream::close_document
                                                          << bsoncxx::builder::stream::finalize;

    try
    {
        coll.update_one(searchFilter, updateData);
    }
    catch (const mongocxx::exception e)
    {
        std::cerr << e.what() << '\n';
    }
}
