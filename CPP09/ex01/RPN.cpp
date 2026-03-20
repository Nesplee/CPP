/* ************************************************************************** */
/*                                                                            */
/*   RPN.cpp                                      C++ Module 09 - STL         */
/*   ex01 : Reverse Polish Notation                                           */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>    // std::istringstream : découper une string en tokens
#include <stdexcept>  // std::runtime_error : exception standard

/* ==========================================================================
**  FORME CANONIQUE
** ========================================================================== */

RPN::RPN()  {}
RPN::RPN(const RPN& other) { (void)other; }
RPN& RPN::operator=(const RPN& other) { (void)other; return *this; }
RPN::~RPN() {}

/* ==========================================================================
**  _isOperator : vérifie si le token est un opérateur valide
** ========================================================================== */
bool RPN::_isOperator(const std::string& token) const
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

/* ==========================================================================
**  _isNumber : vérifie si le token est un entier (chiffre unique < 10)
**
**  Le sujet stipule que les nombres passés en argument sont tous < 10,
**  donc un seul caractère numérique. Un token comme "42" est invalide
**  comme opérande d'entrée (mais le résultat peut dépasser 10).
** ========================================================================== */
bool RPN::_isNumber(const std::string& token) const
{
    if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
        return true;
    return false;
}

/* ==========================================================================
**  evaluate : algorithme RPN principal
**
**  CONCEPT : std::istringstream pour tokeniser
**  -------------------------------------------
**  std::istringstream traite une string comme un flux.
**  L'opérateur >> extrait les tokens séparés par des espaces.
**
**  Exemple : "8 9 * 9 -"
**  1er >> → token = "8"
**  2ème >> → token = "9"
**  3ème >> → token = "*"
**  4ème >> → token = "9"
**  5ème >> → token = "-"
**
**  CONCEPT : ALGORITHME RPN PAS À PAS
**  ------------------------------------
**  Expression : "8 9 * 9 - 9 - 9 - 4 - 1 +"
**
**  Token "8"  → pile: [8]
**  Token "9"  → pile: [8, 9]
**  Token "*"  → dépile 9 et 8, calcule 8*9=72  → pile: [72]
**  Token "9"  → pile: [72, 9]
**  Token "-"  → dépile 9 et 72, calcule 72-9=63 → pile: [63]
**  ... etc.
**
**  IMPORTANT : l'ordre des opérandes compte pour - et / !
**  Si la pile contient [a, b] (b au sommet), l'opération est : a OP b
**  On dépile b (right), puis a (left), et on calcule left OP right.
** ========================================================================== */
int RPN::evaluate(const std::string& expression) const
{
    std::stack<int> stack;   // La pile de travail
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (_isNumber(token))
        {
            // C'est un chiffre : on empile sa valeur numérique
            stack.push(token[0] - '0');  // '7' - '0' = 7 (astuce ASCII)
        }
        else if (_isOperator(token))
        {
            // Il faut au moins 2 opérandes dans la pile
            if (stack.size() < 2)
                throw std::runtime_error("Error");

            /*
            ** Dépiler dans le bon ordre !
            ** top() = dernier empilé = opérande de droite
            */
            int right = stack.top(); stack.pop();
            int left  = stack.top(); stack.pop();

            if (token == "+") stack.push(left + right);
            else if (token == "-") stack.push(left - right);
            else if (token == "*") stack.push(left * right);
            else if (token == "/")
            {
                if (right == 0)
                    throw std::runtime_error("Error");
                stack.push(left / right);
            }
        }
        else
        {
            // Token inconnu (ni chiffre, ni opérateur)
            throw std::runtime_error("Error");
        }
    }

    /*
    ** À la fin, la pile doit contenir EXACTEMENT un élément : le résultat.
    ** - Si elle est vide → expression vide ou invalide
    ** - Si elle contient > 1 élément → trop d'opérandes, pas assez d'opérateurs
    */
    if (stack.size() != 1)
        throw std::runtime_error("Error");

    return stack.top();
}
