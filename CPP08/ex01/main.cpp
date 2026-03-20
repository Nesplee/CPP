#include <iostream>
#include <vector>
#include "Span.hpp"

int main()
{
	// --- Test de base (exemple du sujet) ---
	// Span(5) = conteneur pouvant stocker max 5 entiers
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	// shortestSpan : tableau trié = [3, 6, 9, 11, 17]
	// différences adjacentes : 3, 3, 2, 6 → minimum = 2
	std::cout << sp.shortestSpan() << std::endl;  // Attendu : 2

	// longestSpan : 17 - 3 = 14
	std::cout << sp.longestSpan() << std::endl;   // Attendu : 14

	// --- Test : exception Span plein ---
	try {
		sp.addNumber(42);  // déjà 5 éléments → doit lever une exception
	} catch (std::exception &e) {
		std::cout << "Exception (plein): " << e.what() << std::endl;
	}

	// --- Test : exception pas assez d'éléments ---
	Span empty(5);
	try {
		empty.shortestSpan();  // 0 éléments → exception
	} catch (std::exception &e) {
		std::cout << "Exception (vide): " << e.what() << std::endl;
	}

	Span single(5);
	single.addNumber(42);
	try {
		single.longestSpan();  // 1 seul élément → exception
	} catch (std::exception &e) {
		std::cout << "Exception (1 element): " << e.what() << std::endl;
	}

	// --- Test avec 10000 nombres via addRange ---
	// addRange utilise des itérateurs pour ajouter une plage d'un coup
	Span bigSpan(10000);
	std::vector<int> nums;
	for (int i = 0; i < 10000; ++i)
		nums.push_back(i);  // 0, 1, 2, ..., 9999

	// On passe begin() et end() du vector → addRange itère dessus
	bigSpan.addRange(nums.begin(), nums.end());

	// shortestSpan = 1 (nombres consécutifs)
	// longestSpan  = 9999 - 0 = 9999
	std::cout << "shortestSpan(10000 nums): " << bigSpan.shortestSpan() << std::endl;
	std::cout << "longestSpan(10000 nums): " << bigSpan.longestSpan() << std::endl;

	return 0;
}
