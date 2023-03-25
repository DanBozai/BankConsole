#ifndef MISC_H
#define MISC_H

#pragma once
#include <iostream>
#include <string>
#include <random>

// enum dbKeyName
// {
//     NameKey=1,
//     SurnameKey,
//     PhoneNumberKey,
//     IDKey,
//     IBANKey
// };

enum AccesKeyName
{
    editableKeyPair=4,
    viewKyes=6
};

std::string generateIBAN();
std::string getKeyName(const int getKeyAccess);

#endif