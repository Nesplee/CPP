/* ************************************************************************** */
/*                                                                            */
/*   main.cpp                                     C++ Module 09 - STL         */
/*   ex00 : Bitcoin Exchange                                                  */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

/*
** CONCEPT : argc / argv
** ---------------------
** argc = nombre d'arguments (le nom du programme compte pour 1)
** argv = tableau de chaînes C (char*)
** argv[0] = nom du programme ("./btc")
** argv[1] = premier argument (le fichier d'entrée)
**
** Usage attendu : ./btc input.txt
*/

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./btc <input_file>" << std::endl;
        return 1;
    }

    /*
    ** On instancie BitcoinExchange avec le fichier de base de données.
    ** Le constructeur charge data.csv dans le std::map interne.
    ** Puis processInput() parcourt le fichier d'entrée.
    */
    BitcoinExchange btc("data.csv");
    btc.processInput(argv[1]);

    return 0;
}
