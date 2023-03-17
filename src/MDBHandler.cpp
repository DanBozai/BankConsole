#include "MDBHandler.h"

enum filterSearchENUM
{
    NameCrt = 1,
    SurnameCrt,
    PhoneNumberCrt,
    IBANCrt,

};

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

int MDBHandler::MainMenu()
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
    std::cout << "9.  print documents\n";
    std::cout << "Type corresponding number to initiate a procedure: \n";
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
        break;
    case 9:
        printAllDoccuments();
        break;
    default:
        break;
    }

    return x;
}

std::string MDBHandler::SearchCrtMenu()
{
    int searchMenuInput;
    std::string searchValue;

    std::cout << "Search menu:\n";
    std::cout << "1. Name\n";
    std::cout << "2. Surname\n";
    std::cout << "3. Phone Number\n";
    std::cout << "4. IBAN\n";
    std::cout << "Select a criteria to search:\n";
    std::cin >> searchMenuInput;
    switch (searchMenuInput)
    {
    case NameCrt:
        searchValue = "Name";

        break;
    case SurnameCrt:
        searchValue = "Surname";

        break;
    case PhoneNumberCrt:
        searchValue = "PhoneNumber";
        break;
    case IBANCrt:
        searchValue = "IBAN";

    default:
        break;
    }
    return searchValue;
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
    std::string modifiedInput = "";
    auto builder = document{};

    auto searchFilter = filterSearch();

    auto doc = coll.find_one(searchFilter.view());

    if (doc)
    {
        printOneDocument(doc);

        std::cout << "Type the value you want to change for Name: ";
        std::cin >> modifiedInput;

        bsoncxx::document::view_or_value updateData = builder << "$set" << bsoncxx::builder::stream::open_document
                                                              << "Name"
                                                              << modifiedInput
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
    else
    {
        std::cout << "No matching value for the search filter!\n";
    }
}
void MDBHandler::printOneDocument(mongocxx::stdx::optional<bsoncxx::document::value> &document)
{

    auto field1 = document->view()["Name"].get_string().value.to_string();
    auto field2 = document->view()["Surname"].get_string().value.to_string();
    auto field3 = document->view()["PhoneNumber"].get_string().value.to_string();
    auto field4 = document->view()["Sold"].get_int32().value;
    std::cout << "Name: " << field1 << std::endl;
    std::cout << "Surname: " << field2 << std::endl;
    std::cout << "Phone number: " << field3 << std::endl;
    std::cout << "Sold: " << field4 << std::endl;
}

void MDBHandler::printAllDoccuments()
{
    auto find_one_filtered_result = coll.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("Name", "Iulia")));
    auto cursor_all = coll.find({});
    std::cout << "Collection " << coll.name() << " contains these documents:\n";

    for (auto doc : cursor_all)
    {
        std::cout << bsoncxx::to_json(doc, bsoncxx::ExtendedJsonMode::k_relaxed) << std::endl;
    }
    std::cout << std::endl;
}

bsoncxx::document::view_or_value MDBHandler::filterSearch()
{
    std::string searchCrt = SearchCrtMenu();
    std::string valueToSearch = "";
    std::cout << "search by: " << searchCrt << "\n";
    std::cout << "input value: ";

    std::cin >> valueToSearch;
    std::cout << std::endl;
    auto builder = document{};
    bsoncxx::document::view_or_value searchFilter = builder << searchCrt
                                                            << valueToSearch << bsoncxx::builder::stream::finalize;

    return searchFilter;
}
