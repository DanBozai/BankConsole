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

    void setName();
    void setSurname();
    void setPhoneNumber();
    void setIBAN();
    void setSold();
private:
std::string Name="";
std::string Surname="";
std::string PhoneNumber="";
std::string IBAN="";
unsigned int Sold=0;

bool checkStringLetters(const std::string &tempString);
bool checkStringNumbers(const std::string &tempString);


};

#endif