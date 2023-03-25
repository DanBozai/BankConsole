#include "MDBHandler.h"

enum filterSearchENUM
{
    NameCrt = 1,
    SurnameCrt,
    PhoneNumberCrt,
    IBANCrt,

};
enum SetCrt
{
    setName = 1,
    setSurename,
    setPhoneNumber,
    setIBAN,
    setAccountBalance
};

MDBHandler::MDBHandler()
{
}

MDBHandler::~MDBHandler()
{
}

bool MDBHandler::testConnection()
{

    std::string account = getpass("Enter username account\n");
    std::string password = getpass("Enter password account\n");

    uri_string = "mongodb+srv://" + account + ":" + password + "@cluster0.vyxv6f7.mongodb.net/test";
    password.clear();
    account.clear();
    uri = mongocxx::uri{uri_string};
    conn = mongocxx::client{uri};
    db = conn.database("Bank");
    coll = db.collection("Users");
    try
    {
        auto server_status = conn["admin"].run_command(make_document(kvp("ping", 1)));
        std::cout << "Connection successful!" << std::endl;
        uri_string.clear();
        account.clear();
        password.clear();
        return true;
    }
    catch (const mongocxx::exception &e)
    {
        uri_string.clear();
        account.clear();
        password.clear();
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
    std::cout << "6. Search account\n";
    std::cout << "7. Exit\n";
    std::cout << "9. Print documents\n";
    std::cout << "Type corresponding number to initiate a procedure: \n";
    int input;
    std::cin >> input;
    switch (input)
    {
    case 1:
        system("clear");
        countUsers();
        pause();
        break;
    case 2:
        system("clear");
        createAccount();
        pause();
        break;

    case 3:
        system("clear");
        ModifyExistingAccount();
        pause();
        break;

    case 4:
        system("clear");
        pause();
        break;

    case 5:
        system("clear");
        pause();
        break;

    case 6:
        system("clear");
        searchAccount();
        pause();
        break;

    case 7:
        system("clear");
        x = 7;
        std::cout << "Exit\n"
                  << std::endl;
        conn.reset();
        break;

    case 9:
        system("clear");
        printAllDoccuments();
        pause();
        break;
    default:
        break;
    }

    return x;
}

mongocxx::v_noabi::cursor MDBHandler::MenuSearchFilter()
{
    std::string searchKey = getKeyName(viewKyes);

    auto doc = documentValue(searchKey);
    auto cursor_filtered = coll.find(make_document(kvp(searchKey, doc)));

    return cursor_filtered;
}
bsoncxx::v_noabi::document::value MDBHandler::documentValue(const std::string key)
{

    if (key == "Name" || key == "Surname" || key == "PhoneNumber" || key == "IBAN")
    {
        std::string searchInputValue = "";
        std::cout << "search by: " << key << ": ";
        std::cin >> searchInputValue;

        return make_document(kvp("$eq", searchInputValue));
    }
    else if (key == "AccountBalance")
    {
        int AccountBalance = 0;

        unsigned int menuOptions = 0;
        const std::string keyOperator[5] = {"$eq", "$gt", "$gte", "$lt", "$lte"};

        std::cout << "Search Account balance criteria menu:\n";
        std::cout << "1. Equal value (=)\n";
        std::cout << "2. Greater than value (>)\n";
        std::cout << "3. Greater than equal value (=>)\n";
        std::cout << "4. Lesser than value (<=)\n";
        std::cout << "5. Lesser than equal value (<=)\n";
        std::cin >> menuOptions;
        if (menuOptions >= 0 && menuOptions <= 5)
        {
            std::cout << "search by " << key << " value: ";
            std::cin >> AccountBalance;
            return make_document(kvp(keyOperator[menuOptions - 1], AccountBalance));
        }
        else
        {
            throw std::runtime_error("Invalid $ operator ");
        }
    }

    else
    {
        throw std::runtime_error("Invalid key parameter: " + key);
    }
}

void MDBHandler::countUsers()
{
    std::cout << coll.name() << " database collection contains " << coll.count_documents({}) << " documents" << std::endl;
}

void MDBHandler::createAccount()
{
    Account *UserAccount = new Account();

    auto builder = document{};
    bsoncxx::document::value docValue = builder << "Name" << UserAccount->getName()
                                                << "Surname" << UserAccount->getSurname()
                                                << "PhoneNumber" << UserAccount->getPhoneNumber()
                                                << "IBAN" << UserAccount->getIBAN()
                                                << "AccountBalance" << UserAccount->getAccountBalance()
                                                << "AccountStatus"
                                                << "active"
                                                << bsoncxx::builder::stream::finalize;

    coll.insert_one({docValue});
    delete UserAccount;
}

void MDBHandler::ModifyExistingAccount()
{
    auto searchFilter = filterSearch();

    auto doc = coll.find_one(searchFilter.view());

    if (doc)
    {
        printOneDocument(doc);
        updateOneDocument(searchFilter);
    }
    else
    {
        std::cout << "No matching value for the search filter!\n";
    }
}
void MDBHandler::printOneDocument(mongocxx::stdx::optional<bsoncxx::document::value> &document)
{

    auto Name = document->view()["Name"].get_string().value.to_string();
    auto Surname = document->view()["Surname"].get_string().value.to_string();
    auto PhoneNumber = document->view()["PhoneNumber"].get_string().value.to_string();
    auto AccountBalance = document->view()["AccountBalance"].get_int32().value;
    std::cout << "1. Name: " << Name << std::endl;
    std::cout << "2. Surname: " << Surname << std::endl;
    std::cout << "3. Phone number: " << PhoneNumber << std::endl;
    std::cout << "4. AccountBalance: " << AccountBalance << "$" << std::endl;
}
/// @brief Print all documents in JSON format
void MDBHandler::printAllDoccuments()
{
    auto find_one_filtered_result = coll.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("Name", 1)));
    auto cursor_all = coll.find({});
    std::cout << "Collection " << coll.name() << " contains these documents:\n";

    for (auto doc : cursor_all)
    {
        std::cout << bsoncxx::to_json(doc, bsoncxx::ExtendedJsonMode::k_relaxed) << std::endl;
    }
    std::cout << std::endl;
}

void MDBHandler::printDocument(bsoncxx::v_noabi::document::view &document)
{
    auto Name = document["Name"].get_string().value.to_string();
    auto Surname = document["Surname"].get_string().value.to_string();
    auto ID = document["ID"].get_string().value.to_string();
    auto phoneNum = document["PhoneNumber"].get_string().value.to_string();
    auto IBAN = document["IBAN"].get_string().value.to_string();
    auto AccBalance = document["AccountBalance"].get_int32();
    std::cout << Name << " " << Surname << " ID:" << ID << " " << phoneNum << " " << IBAN << " Account balance:" << AccBalance << "$" << std::endl;
}

bsoncxx::document::view_or_value MDBHandler::filterSearch()
{
    std::cout<<"Select the search criteria"<<std::endl;

    std::string searchCrt = getKeyName(viewKyes);
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

void MDBHandler::updateOneDocument(bsoncxx::document::view_or_value filterSearch)
{
    auto builder = document{};
    std::string modifiedInput = "";

    std::cout << "Select the account information to bind a new modification" << std::endl;
    std::string setKey = getKeyName(editableKeyPair);

    if (!setKey.empty()&& setKey!="AccountBalance")
    {
        std::cout << "Type the value you want to change for " << setKey << ": ";
        std::cin >> modifiedInput;

        bsoncxx::document::view_or_value updateData = builder << "$set" << bsoncxx::builder::stream::open_document
                                                              << setKey
                                                              << modifiedInput
                                                              << bsoncxx::builder::stream::close_document
                                                              << bsoncxx::builder::stream::finalize;
        if (filterSearch.is_owning())
        {

            try
            {
                coll.update_one(filterSearch, updateData);
                std::cout << "Document user "<< setKey<<": "<< modifiedInput<<" updated succesfully\n";
            }
            catch (const mongocxx::exception e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
        {
            std::cout << "The search filter does not have own values\n";
        }
    }
    
}

void MDBHandler::searchAccount()
{

    // auto cursor_filtered = coll.find(make_document(kvp("AccountBalance", make_document(kvp("$gte", 0), kvp("$lte", 22000)))));
    auto cursorFiltered = MenuSearchFilter();

    unsigned int countDocuments = 0;

    for (auto doc : cursorFiltered)
    {

        ++countDocuments;
        std::cout << countDocuments << ". ";
        printDocument(doc);
    }
    std::cout << countDocuments << " documents match the search filter\n";
}

void MDBHandler::pause()
{
    {
        std::cout << "Press Enter to continue\n";
        std::cin.get();
        std::cin.ignore();
        system("clear");
    }
}
