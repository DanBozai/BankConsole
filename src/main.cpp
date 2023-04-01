#include <iostream>
#include <stdio.h>


#include "MDBHandler.h"

int main(int argc, char const *argv[])
{
        MDBHandler* Test= new MDBHandler();
        while (!Test->testConnection())
        {

        }
        while(Test->MainMenu()!=7);

        delete Test;
    return 0;
}
