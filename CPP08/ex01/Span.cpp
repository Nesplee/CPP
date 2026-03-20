#include "Span.hpp"

/*
** Constructeur paramétré
** Initialise la capacité maximale avec N.
** La liste d'initialisation ": _maxSize(N)" est la façon C++ d'initialiser
** les attributs avant que le corps du constructeur ne s'exécute.
*/
Span::Span(unsigned int N) : _maxSize(N) {}

/*
** Constructeur de copie
** Copie la capacité ET tous les entiers stockés.
** std::vector a son propre constructeur de copie qui copie tous les éléments.
*/
Span::Span(const Span &other) : _maxSize(other._maxSize), _numbers(other._numbers) {}

/*
** Opérateur d'affectation
** Vérifie l'auto-affectation (si on fait sp = sp, ne rien faire)
*/
Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}

/*
** Destructeur
** std::vector libère sa mémoire automatiquement, donc rien à faire ici.
*/
Span::~Span() {}

/*
** addNumber : ajoute un entier au Span.
** Lance une exception si le conteneur est déjà plein.
**
** _numbers.size() retourne un size_t (entier non signé).
** On compare avec _maxSize qui est aussi unsigned int → pas de warning.
*/
void Span::addNumber(int n)
{
	if (_numbers.size() >= _maxSize)
		throw std::runtime_error("Span is full: cannot add more numbers");
	_numbers.push_back(n);
}

/*
** shortestSpan : retourne la plus petite différence entre deux éléments.
**
** ALGORITHME :
** 1. Copier le vector (on ne veut pas modifier l'original)
** 2. Trier la copie → les éléments les plus proches sont maintenant adjacents
** 3. Parcourir les paires adjacentes et garder la plus petite différence
**
** Pourquoi trier ? Parce que la plus petite différence entre deux éléments
** quelconques d'un tableau se trouve forcément entre deux éléments adjacents
** dans le tableau trié. C'est une propriété mathématique fondamentale.
*/
int Span::shortestSpan() const
{
	if (_numbers.size() <= 1)
		throw std::runtime_error("Not enough numbers to compute a span");

	// Copie pour ne pas modifier _numbers
	std::vector<int> sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());

	// Initialisation avec la première paire adjacente
	int minSpan = sorted[1] - sorted[0];

	// Parcours des paires adjacentes restantes
	for (size_t i = 1; i < sorted.size() - 1; ++i)
	{
		int span = sorted[i + 1] - sorted[i];
		if (span < minSpan)
			minSpan = span;
	}
	return minSpan;
}

/*
** longestSpan : retourne max - min.
**
** std::max_element et std::min_element parcourent le conteneur et retournent
** des itérateurs vers le plus grand / plus petit élément.
** On déréférence avec * pour obtenir la valeur.
*/
int Span::longestSpan() const
{
	if (_numbers.size() <= 1)
		throw std::runtime_error("Not enough numbers to compute a span");

	int maxVal = *std::max_element(_numbers.begin(), _numbers.end());
	int minVal = *std::min_element(_numbers.begin(), _numbers.end());
	return maxVal - minVal;
}
