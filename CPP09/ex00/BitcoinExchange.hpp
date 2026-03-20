/* ************************************************************************** */
/*                                                                            */
/*   BitcoinExchange.hpp                          C++ Module 09 - STL         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

/*
** CONCEPT : POURQUOI DES INCLUDE GUARDS ?
** ----------------------------------------
** Si deux fichiers .cpp incluent ce header, sans les guards le compilateur
** verrait les déclarations en double → erreur de compilation.
** Le pattern #ifndef / #define / #endif garantit une seule inclusion.
*/

# include <map>      // std::map : conteneur associatif trié (arbre rouge-noir)
# include <string>   // std::string

/*
** CONCEPT : FORME CANONIQUE ORTHODOXE (Orthodox Canonical Form)
** -------------------------------------------------------------
** Obligatoire depuis le Module 02. Toute classe doit définir :
**   1. Constructeur par défaut
**   2. Constructeur de copie
**   3. Opérateur d'affectation (operator=)
**   4. Destructeur
**
** Sans eux, le compilateur génère des versions qui font une copie
** superficielle (shallow copy), dangereuse si la classe gère des ressources.
*/

class BitcoinExchange
{
    public:
        BitcoinExchange(const std::string& dbFile = "data.csv");
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        // Lit le fichier d'entrée et affiche les conversions
        void processInput(const std::string& inputFile) const;

    private:
        /*
        ** CONCEPT : std::map<K, V>
        ** -------------------------
        ** Conteneur associatif ordonné (arbre rouge-noir en interne).
        ** - Clés TRIÉES automatiquement en ordre croissant
        ** - Accès / insertion / suppression : O(log n)
        ** - Chaque clé est UNIQUE
        **
        ** Clé   = date "YYYY-MM-DD" (string ISO 8601)
        ** Valeur = taux de change (double)
        **
        ** ASTUCE : le tri alphabétique de "YYYY-MM-DD" est identique
        ** au tri chronologique → on peut utiliser lower_bound() pour
        ** trouver la date la plus proche directement !
        */
        std::map<std::string, double> _database;

        void        _loadDatabase(const std::string& dbFile);
        bool        _isValidDate(const std::string& date) const;
        bool        _isValidValue(const std::string& valueStr, double& outVal) const;
        std::string _trim(const std::string& s) const;
};

#endif
