#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

/*
** NOTION : std::stack
** std::stack est un adaptateur de conteneur (container adapter).
** Il encapsule un autre conteneur (par défaut std::deque) et expose
** uniquement les opérations d'une pile (LIFO : Last In, First Out) :
**   - push() : empile un élément en haut
**   - pop()  : dépile l'élément du haut
**   - top()  : consulte l'élément du haut
**   - size() : nombre d'éléments
**   - empty(): vrai si vide
**
** Problème : std::stack N'a PAS d'itérateurs. On ne peut pas parcourir
** les éléments un par un avec begin()/end().
**
** NOTION : HÉRITAGE DE TEMPLATE
** En héritant de std::stack<T>, MutantStack récupère TOUTES les fonctions
** membre de std::stack ET on peut y ajouter des fonctionnalités.
**
** NOTION : Membre protégé "c"
** std::stack expose son conteneur interne via un membre protégé nommé "c"
** (de type Container, par défaut std::deque<T>).
** Comme MutantStack hérite de std::stack, on peut accéder à "c" directement.
** C'est ce qui nous permet d'exposer begin() et end().
**
** NOTION : typedef
** "typedef typename std::stack<T>::container_type::iterator iterator;"
** crée un alias "iterator" pour le type d'itérateur du conteneur interne.
** Cela permet d'écrire "MutantStack<int>::iterator" plutôt que l'expression longue.
** Le mot-clé "typename" est nécessaire car le compilateur doit savoir que
** container_type::iterator est un TYPE et non un membre de données.
*/

#include <stack>   // std::stack
#include <deque>   // std::deque (conteneur par défaut de stack)

template <typename T>
class MutantStack : public std::stack<T>
{
public:
	// Constructeur par défaut : appelle simplement le constructeur de std::stack
	MutantStack() {}

	// Constructeur de copie : délègue à std::stack
	MutantStack(const MutantStack &other) : std::stack<T>(other) {}

	// Opérateur d'affectation : délègue à std::stack
	MutantStack &operator=(const MutantStack &other)
	{
		if (this != &other)
			std::stack<T>::operator=(other);
		return *this;
	}

	// Destructeur
	~MutantStack() {}

	/*
	** Définition des types d'itérateurs.
	** container_type est le type du conteneur interne (std::deque<T> par défaut).
	** On expose son iterator et const_iterator sous des noms plus courts.
	*/
	typedef typename std::stack<T>::container_type::iterator       iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;

	/*
	** begin() : retourne un itérateur sur le PREMIER élément du conteneur interne.
	** Dans une deque, le premier élément est le "fond" de la pile.
	**
	** "std::stack<T>::c" est le membre protégé (le conteneur sous-jacent).
	** Comme MutantStack hérite de std::stack, on peut y accéder directement.
	*/
	iterator begin()
	{
		return std::stack<T>::c.begin();
	}

	// end() : retourne un itérateur sur l'élément APRÈS le dernier (sentinelle)
	iterator end()
	{
		return std::stack<T>::c.end();
	}

	// Versions const pour les objets const
	const_iterator begin() const
	{
		return std::stack<T>::c.begin();
	}

	const_iterator end() const
	{
		return std::stack<T>::c.end();
	}
};

/*
** Note : toute l'implémentation est dans le .hpp car c'est une classe template.
** Le compilateur a besoin de voir le code complet au moment de l'instanciation.
*/

#endif
