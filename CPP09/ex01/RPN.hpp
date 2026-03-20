/* ************************************************************************** */
/*                                                                            */
/*   RPN.hpp                                      C++ Module 09 - STL         */
/*   ex01 : Reverse Polish Notation                                           */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>   // std::stack : adaptateur de conteneur LIFO
# include <string>  // std::string

/*
** CONCEPT : std::stack<T>
** -----------------------
** std::stack N'EST PAS un conteneur, c'est un "adaptateur de conteneur".
** Il enveloppe un conteneur sous-jacent (std::deque par défaut) et
** n'expose qu'une interface restreinte :
**
**   push(val)   → empile val au sommet              O(1)
**   pop()       → retire l'élément du sommet        O(1)  /!\ ne retourne rien
**   top()       → consulte l'élément du sommet      O(1)
**   size()      → nombre d'éléments dans la pile    O(1)
**   empty()     → vrai si la pile est vide          O(1)
**
** Pourquoi un adaptateur plutôt qu'un vrai conteneur ?
** Parce que la sémantique LIFO est garantie par construction :
** on ne peut pas accéder à n'importe quel élément, seulement au sommet.
** Cela rend le code auto-documenté et évite les erreurs.
**
** CONCEPT : LIFO (Last In, First Out)
** ------------------------------------
** L'algorithme RPN repose entièrement sur cette propriété :
**   - On lit un token
**   - Si c'est un nombre → on l'EMPILE (push)
**   - Si c'est un opérateur → on DÉPILE les 2 derniers nombres,
**     on effectue l'opération, on EMPILE le résultat
**   - À la fin, il doit rester exactement 1 valeur dans la pile = le résultat
*/

class RPN
{
    public:
        RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();

        /*
        ** evaluate() prend une expression RPN (ex: "8 9 * 9 - 4 -")
        ** et retourne le résultat sous forme de string (pour affichage).
        ** Lance une std::runtime_error si l'expression est invalide.
        */
        int evaluate(const std::string& expression) const;

    private:
        bool _isOperator(const std::string& token) const;
        bool _isNumber(const std::string& token) const;
};

#endif
