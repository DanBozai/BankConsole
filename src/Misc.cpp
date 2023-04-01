#include "Misc.h"
/// @brief IBAN Generator
/// @return "ROITSCHOOL"+ "14 random int converted to char "
std::string generateIBAN()
{
    std::string tempIBAN = "ROITSCHOOL";
    unsigned int randomNumberSize = 15;
    std::random_device randomDevice;

    std::mt19937 gen(randomDevice());

    std::uniform_int_distribution<> distribution(48, 57);

    for (int i = 0; i < 15; i++)
    {
        int randomNumber = distribution(gen);
        tempIBAN.push_back(char(randomNumber));
    }
    return tempIBAN;
}
/// @brief string function to get all the database Key and display the option menu (this function contain a keyName array(Name", "Surname", "PhoneNumber", "ID", "AccountBalance","IBAN"))
/// @param getKeyAccess const int parameter (Enum AccesKeyName editableKeyPair=4,  viewKyes=6) to interact in certain conditions with some functions 
/// @return string key
std::string getKeyName(const int getKeyAccess)
{
    std::string keyNameArr[6] = {"Name", "Surname", "PhoneNumber", "ID", "AccountBalance","IBAN"};

    int inputOptions = 0;
    std::cout << "Options:\n";
    if (getKeyAccess == viewKyes)
    {
        for (int i = 0; i < viewKyes; i++)
        {
            std::cout << i + 1 << "." << keyNameArr[i] << std::endl;
        }

        std::cin >> inputOptions;

        if (inputOptions >= 0 && inputOptions <= viewKyes)
        {
            return keyNameArr[inputOptions - 1];
        }
        else
        {

            throw std::runtime_error("Invalid input option for viewKeys ");
        }
    }
    else if (getKeyAccess == editableKeyPair)
    {
        for (int i = 0; i < editableKeyPair; i++)
        {
            std::cout << i + 1 << "." << keyNameArr[i] << std::endl;
        }
        std::cin >> inputOptions;

        if (inputOptions >= 0 && inputOptions <= editableKeyPair)
        {
            return keyNameArr[inputOptions - 1];
        }
        else
        {

            throw std::runtime_error("Invalid input option for editableKeyPair");
        }
    }
    throw std::runtime_error("Invalid parameter for const int getKeyAccess");
}