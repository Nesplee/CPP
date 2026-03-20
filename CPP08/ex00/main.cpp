#include <iostream>
#include <vector>   // conteneur vector
#include <list>     // conteneur list
#include "easyfind.hpp"

int main()
{
	// --- Test avec un vector<int> ---
	// vector = tableau dynamique, accès aléatoire O(1)
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	// Cas 1 : valeur présente → doit afficher 3
	try {
		std::vector<int>::iterator it = easyfind(v, 3);
		std::cout << "Found in vector: " << *it << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	// Cas 2 : valeur absente → doit lever une exception
	try {
		std::vector<int>::iterator it = easyfind(v, 10);
		std::cout << "Found in vector: " << *it << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// --- Test avec un list<int> ---
	// list = liste doublement chaînée, pas d'accès aléatoire
	// mais insertions/suppressions en O(1)
	std::list<int> l;
	l.push_back(10);
	l.push_back(20);
	l.push_back(30);

	// Cas 3 : valeur présente dans la liste → doit afficher 20
	try {
		std::list<int>::iterator it = easyfind(l, 20);
		std::cout << "Found in list: " << *it << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	// Cas 4 : valeur absente dans la liste → exception
	try {
		std::list<int>::iterator it = easyfind(l, 99);
		std::cout << "Found in list: " << *it << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
