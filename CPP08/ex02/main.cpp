#include <iostream>
#include <list>    // pour la comparaison finale avec std::list
#include "MutantStack.hpp"

int main()
{
	// --- Test principal (exemple du sujet) ---
	// MutantStack<int> se comporte comme std::stack<int> MAIS est itérable
	MutantStack<int> mstack;

	mstack.push(5);   // empile 5   → pile : [5]
	mstack.push(17);  // empile 17  → pile : [5, 17]

	// top() donne le sommet de la pile (dernier empilé)
	std::cout << mstack.top() << std::endl;  // Attendu : 17

	// pop() dépile l'élément du sommet
	mstack.pop();  // pile : [5]

	// size() retourne le nombre d'éléments
	std::cout << mstack.size() << std::endl;  // Attendu : 1

	mstack.push(3);    // pile : [5, 3]
	mstack.push(5);    // pile : [5, 3, 5]
	mstack.push(737);  // pile : [5, 3, 5, 737]
	// [...]
	mstack.push(0);    // pile : [5, 3, 5, 737, 0]

	// Déclaration d'un itérateur (begin = fond de la pile, end = après le sommet)
	MutantStack<int>::iterator it  = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	// Test des opérateurs d'itérateur : ++ (avancer), -- (reculer)
	++it;
	--it;

	// Parcours de tous les éléments (du fond vers le sommet)
	while (it != ite)
	{
		std::cout << *it << std::endl;  // *it déréférence l'itérateur
		++it;
	}

	// --- Vérification : même résultat avec std::stack (copie vers stack) ---
	// std::stack<int> s(mstack) fonctionne car MutantStack hérite de std::stack
	std::stack<int> s(mstack);
	(void)s;  // évite le warning "unused variable"

	// --- Test de comparaison avec std::list ---
	// Le sujet demande que le résultat soit identique si on remplace
	// MutantStack par un autre conteneur (en adaptant push/pop → push_back/pop_back)
	std::cout << "\n--- Même test avec std::list ---" << std::endl;
	std::list<int> lst;
	lst.push_back(5);
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	std::list<int>::iterator lit  = lst.begin();
	std::list<int>::iterator lite = lst.end();

	while (lit != lite)
	{
		std::cout << *lit << std::endl;
		++lit;
	}

	return 0;
}
