#include "Account.h"

Account::Account()
{
    setName();
    setSurname();
    setPhoneNumber();
    setIBAN();
}


Account::~Account()
{
}

std::string Account::getName()
{
    return Name;
}

std::string Account::getSurname()
{
    return Surname;
}

std::string Account::getPhoneNumber()
{
    return PhoneNumber;
}

std::string Account::getIBAN()
{
    return IBAN;
}
int Account::getAccountBalance()
{
    return AccountBalance;
}

void Account::setName()
{
    system("clear");

    bool isChar = false;
    std::string tempName = "";
    do
    {
        std::cout << "Enter the name: ";

        std::cin >> tempName;

        if (checkStringLetters(tempName))
        {
            Name = tempName;
            isChar = true;
            break;
        }
        else
        {
            isChar = false;
            system("clear");

            std::cout << "Invalid input for name, please rewrite the Name(only letters)\n";
            tempName.clear();
        }
    } while (!isChar);

    std::cout << std::endl;
}

void Account::setSurname()
{
    system("clear");

    bool isChar = false;
    std::string tempName = "";
    do
    {
        std::cout << "Enter the surname: ";

        std::cin >> tempName;

        if (checkStringLetters(tempName))
        {
            Surname = tempName;
            isChar = true;
            break;
        }
        else
        {
            isChar = false;
            system("clear");

            std::cout << "Invalid input for surname, please rewrite the surname(only letters)\n";
            tempName.clear();
        }
    } while (!isChar);
}

void Account::setPhoneNumber()
{
    system("clear");

    bool isChar = false;
    std::string tempPhoneNumber = "";
    do
    {
        std::cout << "Enter the phone number: ";

        std::cin >> tempPhoneNumber;

        if (checkStringNumbers(tempPhoneNumber))
        {
            PhoneNumber = tempPhoneNumber;
            isChar = true;
            break;
        }
        else
        {
            isChar = false;
            system("clear");

            std::cout << "Invalid input for phonenumber, please rewrite the phone number(only numbers)\n";
            tempPhoneNumber.clear();
        }
    } while (!isChar);
}

void Account::setIBAN()
{
    
    IBAN = generateIBAN();
}

void Account::setAccountBalance()
{
    int input = 0;
    std::cout << "1. Add balance\n";
    std::cout << "2. Continue \n";
    switch (1)
    {
    case 1:
        std::cout << "Enter the amount of money you want to add: \n";
        std::cin >> AccountBalance;
        break;

    default:
        AccountBalance = 0;
        std::cout << "AccountBalance =" << AccountBalance << std::endl;

        break;
    }
    std::cin >> AccountBalance;
}

bool Account::checkStringLetters(const std::string &tempString)
{
    bool isValid = false;

    for (int i = 0; i < tempString.size(); i++)
    {

        if (int(tempString.at(i)) >= 97 && int(tempString.at(i)) <= 122)
        {
            isValid = true;
        }
        else if (int(tempString.at(i)) >= 65 && int(tempString.at(i)) <= 90)
        {
            isValid = true;
        }
        else
        {
            isValid = false;
            break;
        }
    }

    return isValid;
}

bool Account::checkStringNumbers(const std::string &tempString)
{
    bool isValid = false;
    const unsigned int phoneNumberSize = 7;

    for (int i = 0; i < tempString.size(); i++)
    {
        if (tempString.size() != phoneNumberSize)
        {
            isValid = false;
            break;
        }
        else if (int(tempString.at(i)) >= 48 && int(tempString.at(i)) <= 57)
        {

            isValid = true;
        }
        else
        {
            isValid = false;
            break;
        }
    }

    return isValid;
}