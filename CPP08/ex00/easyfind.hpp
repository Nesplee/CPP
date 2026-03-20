#ifndef EASYFIND_HPP
#define EASYFIND_HPP

/*
** NOTION : FONCTION TEMPLATE
** Une fonction template permet d'écrire du code générique qui fonctionne
** avec n'importe quel type. Ici, T représente n'importe quel conteneur STL
** (vector, list, deque...). Le compilateur génère automatiquement la version
** concrète de la fonction selon le type passé en paramètre.
**
** NOTION : std::find (algorithme STL)
** std::find parcourt un conteneur entre deux itérateurs (begin et end)
** et retourne un itérateur sur le premier élément égal à la valeur cherchée.
** Si rien n'est trouvé, il retourne end().
**
** NOTION : Itérateurs
** Un itérateur est un objet qui "pointe" vers un élément d'un conteneur.
** container.begin() pointe vers le premier élément.
** container.end()   pointe APRÈS le dernier élément (sentinelle).
*/

#include <algorithm>   // pour std::find
#include <stdexcept>   // pour std::runtime_error

/*
** easyfind<T>(container, value)
**
** Paramètres :
**   - container : un conteneur STL d'entiers (vector<int>, list<int>, etc.)
**   - value     : l'entier à chercher dans le conteneur
**
** Retour : un itérateur pointant sur la première occurrence de value.
** Exception : std::runtime_error si value n'est pas trouvé.
**
** Note : T doit être un conteneur séquentiel (pas de map/set car ils
** n'ont pas de parcours linéaire sur les valeurs seules).
*/
template <typename T>
typename T::iterator easyfind(T &container, int value)
{
	// std::find cherche 'value' entre begin() et end()
	// et retourne un itérateur sur l'élément trouvé (ou end() si absent)
	typename T::iterator it = std::find(container.begin(), container.end(), value);

	// Si l'itérateur vaut end(), c'est que l'élément n'a pas été trouvé
	if (it == container.end())
		throw std::runtime_error("Value not found in container");

	return it;
}

#endif
