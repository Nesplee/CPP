#include <iostream>
#include <vector>
#include "Span.hpp"

int main()
{
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	try {
		sp.addNumber(42);
	} catch (std::exception &e) {
		std::cout << "Exception (plein): " << e.what() << std::endl;
	}
	Span empty(5);
	try {
		empty.shortestSpan();
	} catch (std::exception &e) {
		std::cout << "Exception (vide): " << e.what() << std::endl;
	}
	Span single(5);
	single.addNumber(42);
	try {
		single.longestSpan();
	} catch (std::exception &e) {
		std::cout << "Exception (1 element): " << e.what() << std::endl;
	}
	Span bigSpan(10000);
	std::vector<int> nums;
	for (int i = 0; i < 10000; ++i)
		nums.push_back(i);
	bigSpan.addRange(nums.begin(), nums.end());
	std::cout << "shortestSpan(10000 nums): " << bigSpan.shortestSpan() << std::endl;
	std::cout << "longestSpan(10000 nums): " << bigSpan.longestSpan() << std::endl;
	return 0;
}
