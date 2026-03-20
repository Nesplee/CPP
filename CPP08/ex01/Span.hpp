#ifndef SPAN_HPP
#define SPAN_HPP

/*
** NOTION : CLASSE EN FORME CANONIQUE ORTHODOXE
** Toute classe doit avoir :
**   1. Constructeur par défaut (ou paramétré)
**   2. Constructeur de copie
**   3. Opérateur d'affectation
**   4. Destructeur
**
** NOTION : SPAN (étendue)
** Un "span" entre deux nombres est la différence absolue entre eux.
** shortestSpan = plus petite différence entre deux éléments du conteneur.
** longestSpan  = différence entre le max et le min du conteneur.
*/

#include <vector>      // pour stocker les entiers
#include <stdexcept>   // pour les exceptions
#include <algorithm>   // pour std::sort, std::min_element, std::max_element

class Span
{
public:
	// Constructeur : N est la capacité maximale du Span
	Span(unsigned int N);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();

	// Ajoute un seul entier. Lance une exception si le Span est plein.
	void addNumber(int n);

	/*
	** NOTION : MÉTHODE TEMPLATE dans une classe non-template
	** On peut avoir une seule méthode template dans une classe normale.
	** Ici, Iterator représente n'importe quel type d'itérateur
	** (vector::iterator, list::iterator, int*, etc.)
	**
	** Cette méthode permet d'ajouter une plage d'éléments en un seul appel,
	** ce qui est bien plus pratique que d'appeler addNumber() des milliers de fois.
	**
	** Note : l'implémentation DOIT être dans le .hpp car c'est un template.
	*/
	template <typename Iterator>
	void addRange(Iterator begin, Iterator end)
	{
		for (Iterator it = begin; it != end; ++it)
			addNumber(*it);  // *it déréférence l'itérateur pour obtenir la valeur
	}

	// Retourne la plus petite différence entre deux éléments adjacents (après tri)
	int shortestSpan() const;

	// Retourne max - min (la plus grande différence possible)
	int longestSpan() const;

private:
	unsigned int     _maxSize;   // capacité maximale
	std::vector<int> _numbers;   // les entiers stockés
};

#endif
