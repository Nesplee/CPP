#include <iostream>
#include <cstdlib>
#include "Array.hpp"
#include <ctime>

#define MAX_VAL 750

struct Tracker {
	int v;
	Tracker() : v(0) {}
	Tracker(int x) : v(x) {}
};

static int	g_failures = 0;

#define CHECK(cond, msg) \
	do { \
		if (!(cond)) { \
			std::cerr << "FAIL: " << msg << std::endl; \
			g_failures++; \
		} else { \
			std::cout << "OK: " << msg << std::endl; \
		} \
	} while (0)

int main(int, char**)
{
	(void)MAX_VAL;

	// 1) Constructeur par défaut
	{
		Array<int> a;
		CHECK(a.size() == 0, "default constructor: size()==0");
		try {
			a[0] = 1;
			CHECK(false, "default constructor: out-of-bounds throws");
		} catch (std::exception const& e) {
			std::cout << "exception caught: " << e.what() << std::endl;
			CHECK(true, "default constructor: out-of-bounds throws");
		}
	}

	// 2) Constructeur avec n : initialisation par défaut
	{
		Array<int> a(5);
		CHECK(a.size() == 5, "constructor(n): size()==n");
		CHECK(a[0] == 0 && a[4] == 0, "constructor(n): default initialization");
	}

	// 3) Copie profonde (copy constructor)
	{
		Array<int> src(3);
		src[0] = 10; src[1] = 20; src[2] = 30;
		Array<int> copy(src);

		src[1] = 999;
		CHECK(copy[1] == 20, "copy constructor: deep copy (independence)");
	}

	// 4) Copie profonde (operator=)
	{
		Array<int> a(2);
		a[0] = 1; a[1] = 2;

		Array<int> b(2);
		b[0] = 7; b[1] = 8;

		a = b;
		b[1] = 4242;
		CHECK(a[1] == 8, "assignment operator: deep copy (independence)");
	}

	// 5) Self-assignment
	{
		Array<int> a(2);
		a[0] = 3; a[1] = 4;
		a = a;
		CHECK(a[0] == 3 && a[1] == 4, "self-assignment: no corruption");
	}

	// 6) Const operator[]
	{
		Array<Tracker> a(3);
		a[0] = Tracker(1);
		a[1] = Tracker(2);
		a[2] = Tracker(3);

		const Array<Tracker> ca = a;
		CHECK(ca[2].v == 3, "const operator[] works");
	}

	// 7) Exceptions out-of-bounds
	{
		Array<int> a(3);

		try {
			a[3] = 0;
			CHECK(false, "operator[]: index==size throws");
		} catch (std::exception const&) {
			CHECK(true, "operator[]: index==size throws");
		}

		try {
			a[(unsigned int)-1] = 0;
			CHECK(false, "operator[]: negative index converted throws");
		} catch (std::exception const&) {
			CHECK(true, "operator[]: negative index converted throws");
		}
	}

	// 8) Petit stress pour forcer la destruction
	{
		for (int i = 0; i < 100; i++) {
			Array<int> a((unsigned int)(i % 10));
			for (unsigned int j = 0; j < a.size(); j++)
				a[j] = (int)j;
		}
		CHECK(true, "stress loop: runs without crash");
	}

	if (g_failures != 0)
		return 1;
	return 0;
}
