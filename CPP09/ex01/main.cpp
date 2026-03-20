/* ************************************************************************** */
/*                                                                            */
/*   main.cpp                                     C++ Module 09 - STL         */
/*   ex01 : Reverse Polish Notation                                           */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <stdexcept>  // std::runtime_error

/*
** Usage : ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
**
** L'expression entière est passée comme un SEUL argument entre guillemets.
** argv[1] contient donc la string complète.
*/

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./RPN \"<expression>\"" << std::endl;
        return 1;
    }

    RPN rpn;

    try
    {
        /*
        ** CONCEPT : try / catch / throw
        ** --------------------------------
        ** try     : bloc de code susceptible de lancer une exception
        ** throw   : lance une exception (ici depuis RPN::evaluate)
        ** catch   : intercepte l'exception et gère l'erreur
        **
        ** En C++98, on utilise std::exception et ses dérivées
        ** (std::runtime_error, std::invalid_argument, etc.)
        ** plutôt que des codes de retour, car les exceptions remontent
        ** automatiquement la pile d'appel sans polluer les signatures.
        */
        int result = rpn.evaluate(argv[1]);
        std::cout << result << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
