#ifndef MISC_H
#define MISC_H

#pragma once
#include <iostream>
#include <string>
#include <random>


enum AccesKeyName
{
    editableKeyPair=4,
    viewKyes=6
};

std::string generateIBAN();
std::string getKeyName(const int getKeyAccess);

#endif