#ifndef ACCOUNT_H
#define ACCOUNT_H

#pragma once
#include <string>
#include <iostream>
#include <random>

class Account
{
public:
    Account();
    ~Account();

    std::string getName();
    std::string getSurname();
    std::string getPhoneNumber();
    std::string getIBAN();
    int getAccountBalance();

private:
    std::string Name = "";
    std::string Surname = "";
    std::string PhoneNumber = "";
    std::string IBAN = "";
    unsigned int AccountBalance = 0;

    void setName();
    void setSurname();
    void setPhoneNumber();
    void setIBAN();
    void setAccountBalance();

    bool checkStringLetters(const std::string &tempString);
    bool checkStringNumbers(const std::string &tempString);
};

#endif