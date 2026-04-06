#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>

class Span
{
public:
	Span(unsigned int N);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();
	void addNumber(int n);

	template <typename Iterator>
	void addRange(Iterator begin, Iterator end)
	{
		for (Iterator it = begin; it != end; ++it)
			addNumber(*it);
	}
	int shortestSpan() const;
	int longestSpan() const;

private:
	unsigned int     _maxSize;
	std::vector<int> _numbers;
};

#endif
