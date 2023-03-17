#include <iostream>

#include "MDBHandler.h"
int main(int argc, char const *argv[])
{
    MDBHandler* Test= new MDBHandler();
    while (!Test->testConnection())
    {
        
    }
    Test->MainMenu();

    
    delete Test;
    return 0;
}
