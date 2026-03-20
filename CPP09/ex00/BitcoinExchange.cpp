/* ************************************************************************** */
/*                                                                            */
/*   BitcoinExchange.cpp                          C++ Module 09 - STL         */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>   // std::cout, std::cerr
#include <fstream>    // std::ifstream : lecture de fichiers
#include <cstdlib>    // std::strtod : conversion string → double (C++98)

/* ==========================================================================
**  FORME CANONIQUE
** ========================================================================== */

BitcoinExchange::BitcoinExchange(const std::string& dbFile)
{
    _loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    : _database(other._database)  // std::map a un constructeur de copie
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)           // Garde contre l'auto-affectation (a = a)
        _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/* ==========================================================================
**  _trim : supprime les espaces en début et fin de chaîne
**
**  CONCEPT : std::string methods
**  find_first_not_of / find_last_not_of retournent la position du premier
**  caractère qui n'est PAS dans le set donné.
**  substr(start, length) extrait une sous-chaîne.
** ========================================================================== */
std::string BitcoinExchange::_trim(const std::string& s) const
{
    const std::string whitespace = " \t\r\n";
    size_t start = s.find_first_not_of(whitespace);
    if (start == std::string::npos)  // Que des espaces
        return "";
    size_t end = s.find_last_not_of(whitespace);
    return s.substr(start, end - start + 1);
}

/* ==========================================================================
**  _loadDatabase : charge data.csv dans _database (std::map)
**
**  CONCEPT : std::ifstream
**  Représente un flux d'entrée vers un fichier. On l'ouvre à la construction,
**  et il se ferme automatiquement à la destruction (RAII).
**
**  CONCEPT : std::getline(flux, string)
**  Lit une ligne complète depuis le flux jusqu'au '\n'.
**
**  CONCEPT : std::istringstream
**  Traite une string comme un flux : on peut utiliser >> pour en extraire
**  des tokens (mots, nombres…) exactement comme on lirait depuis std::cin.
** ========================================================================== */
void BitcoinExchange::_loadDatabase(const std::string& dbFile)
{
    std::ifstream file(dbFile.c_str());  // .c_str() requis en C++98
    if (!file.is_open())
    {
        std::cerr << "Error: could not open database file: " << dbFile << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Sauter l'en-tête "date,exchange_rate"

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        // Le CSV utilise ',' comme séparateur
        size_t comma = line.find(',');
        if (comma == std::string::npos) continue;

        std::string date  = _trim(line.substr(0, comma));
        std::string rateStr = _trim(line.substr(comma + 1));

        // Conversion string → double avec strtod (compatible C++98)
        char* endPtr;
        double rate = std::strtod(rateStr.c_str(), &endPtr);
        if (*endPtr != '\0') continue; // Conversion échouée

        /*
        ** CONCEPT : insertion dans std::map avec operator[]
        ** _database[date] = rate;
        ** Si la clé 'date' n'existe pas, elle est créée avec valeur par défaut (0),
        ** puis on lui affecte 'rate'. Sinon, on écrase la valeur existante.
        **
        ** Alternative : _database.insert(std::make_pair(date, rate));
        ** insert() ne remplace PAS si la clé existe déjà.
        */
        _database[date] = rate;
    }
}

/* ==========================================================================
**  _isValidDate : valide le format YYYY-MM-DD et les valeurs calendaires
** ========================================================================== */
bool BitcoinExchange::_isValidDate(const std::string& date) const
{
    // Format strict : exactement 10 caractères "AAAA-MM-JJ"
    if (date.size() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    // Vérifier que tous les autres caractères sont des chiffres
    for (size_t i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }

    // Extraire et valider les composantes
    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31)     return false;
    if (year < 0)                return false;

    // Jours max par mois (simplifié)
    int daysInMonth[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day > daysInMonth[month]) return false;

    return true;
}

/* ==========================================================================
**  _isValidValue : valide la valeur fournie dans le fichier d'entrée
**
**  CONCEPT : strtod vs atof
**  strtod est préférable à atof car il fournit un endPtr qui permet
**  de détecter si la conversion s'est arrêtée avant la fin de la chaîne
**  (ex: "3.5abc" → endPtr pointe sur 'a' → conversion partielle détectée).
** ========================================================================== */
bool BitcoinExchange::_isValidValue(const std::string& valueStr, double& outVal) const
{
    if (valueStr.empty()) return false;

    char* endPtr;
    outVal = std::strtod(valueStr.c_str(), &endPtr);

    // endPtr doit pointer sur '\0' : toute la chaîne a été convertie
    if (*endPtr != '\0') return false;
    if (outVal < 0)      return false;  // Valeur négative interdite
    if (outVal > 1000)   return false;  // Valeur > 1000 interdite

    return true;
}

/* ==========================================================================
**  processInput : traite le fichier d'entrée ligne par ligne
**
**  CONCEPT : lower_bound() — l'opération clé de cet exercice
**  -------------------------------------------------------
**  std::map::lower_bound(key) retourne un itérateur vers le PREMIER élément
**  dont la clé est >= key, en O(log n).
**
**  Exemple avec _database = { "2010-01-01", "2011-06-15", "2012-03-20" }
**  lower_bound("2011-09-01") → itérateur sur "2012-03-20" (première clé >= )
**  On recule d'un pas (--it) pour obtenir "2011-06-15" (la plus proche ≤)
**
**  CONCEPT : itérateurs de std::map
**  Un itérateur de map est une paire (it->first = clé, it->second = valeur).
**  begin() → premier élément, end() → "sentinelle" après le dernier élément.
** ========================================================================== */
void BitcoinExchange::processInput(const std::string& inputFile) const
{
    std::ifstream file(inputFile.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Sauter l'en-tête "date | value"

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        // Séparateur attendu : " | "
        size_t sep = line.find('|');
        if (sep == std::string::npos)
        {
            std::cerr << "Error: bad input => " << _trim(line) << std::endl;
            continue;
        }

        std::string date     = _trim(line.substr(0, sep));
        std::string valueStr = _trim(line.substr(sep + 1));

        // Valider la date
        if (!_isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        // Valider et extraire la valeur
        double value;
        if (!_isValidValue(valueStr, value))
        {
            // Message d'erreur contextuel selon le problème
            char* endPtr;
            double tmp = std::strtod(valueStr.c_str(), &endPtr);
            if (*endPtr != '\0')
                std::cerr << "Error: bad input => " << valueStr << std::endl;
            else if (tmp < 0)
                std::cerr << "Error: not a positive number." << std::endl;
            else
                std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        /*
        ** RECHERCHE DANS LE MAP : lower_bound
        **
        ** lower_bound(date) → premier élément avec clé >= date
        **
        ** Cas 1 : it == begin() → toutes les clés sont > date
        **         Aucune date antérieure disponible dans la DB.
        ** Cas 2 : it->first == date → correspondance exacte, pas besoin de reculer
        ** Cas 3 : it->first > date → on recule (--it) pour avoir la clé <= date
        ** Cas 4 : it == end() → date > toutes les clés → on recule pour prendre
        **         la dernière entrée disponible
        */
        std::map<std::string, double>::const_iterator it = _database.lower_bound(date);

        if (it == _database.end() || it->first != date)
        {
            if (it == _database.begin())
            {
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }
            --it; // Reculer vers la date la plus proche inférieure
        }

        // Affichage : "date => value = result"
        std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
    }
}
