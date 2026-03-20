/* ************************************************************************** */
/*                                                                            */
/*   main.cpp                                     C++ Module 09 - STL         */
/*   ex02 : PmergeMe                                                          */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <stdexcept>

/*
** Usage : ./PmergeMe 3 5 9 7 4
** ou    : ./PmergeMe `shuf -i 1-100000 -n 3000 | tr '\n' ' '`
*/

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./PmergeMe <integer sequence>" << std::endl;
        return 1;
    }

    PmergeMe pmerge;

    try
    {
        pmerge.sort(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
