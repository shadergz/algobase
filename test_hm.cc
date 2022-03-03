/*
 *  Source code written by Gabriel Correia
*/

#include "hashmap.hh"

int main ()
{
    hashmap gabriel;
    gabriel.insert ("Name", "Gabriel Correia");
    gabriel.insert ("ID", "10010219");
    gabriel.insert ("DEV", "Maybe :)");
    
    std::cout << "User Name: " << gabriel["Name"] << std::endl;
    std::cout << "User ID: " << gabriel["ID"] << std::endl;
    std::cout << "Is user a developer: " << gabriel["DEV"] << std::endl;

    return 0;
}

