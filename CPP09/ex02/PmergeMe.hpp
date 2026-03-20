/* ************************************************************************** */
/*                                                                            */
/*   PmergeMe.hpp                                 C++ Module 09 - STL         */
/*   ex02 : PmergeMe — Ford-Johnson merge-insert sort                         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>    // std::vector : tableau dynamique
# include <deque>     // std::deque  : file à double extrémité
# include <string>    // std::string

/*
** CONCEPT : std::vector<T>
** -------------------------
** Tableau dynamique alloué en mémoire contiguë.
** Accès aléatoire en O(1) via operator[] ou .at()
** Insertion en fin (push_back) : O(1) amorti
** Insertion au milieu : O(n) (déplace tous les éléments suivants)
** Idéal quand on accède souvent par indice, rarement en milieu.
**
** CONCEPT : std::deque<T> (double-ended queue)
** ---------------------------------------------
** File à double extrémité. Mémoire allouée par blocs (pas contiguë).
** Accès aléatoire en O(1) mais plus lent que vector (indirection)
** Insertion en début ET en fin : O(1)
** Insertion au milieu : O(n)
** Idéal quand on insère souvent aux deux extrémités.
**
** POURQUOI LES DEUX ?
** Le sujet impose d'implémenter Ford-Johnson avec 2 conteneurs différents
** et de mesurer le temps d'exécution de chacun. Cela illustre que le
** même algorithme peut avoir des performances différentes selon le conteneur
** (localité cache, coût d'insertion, etc.).
**
** CONCEPT : FORD-JOHNSON (merge-insert sort)
** -------------------------------------------
** Algorithme optimal en nombre de comparaisons pour trier n éléments.
** Référence : TAOCP Vol.3, Knuth, p.184.
**
** Les 3 phases :
**   Phase 1 — Former des PAIRES et trier chaque paire (1 comparaison/paire)
**             Le plus grand de chaque paire forme la "main chain" (chaîne principale).
**             Le plus petit devient un "pend" (pendant).
**
**   Phase 2 — Trier récursivement la main chain par Ford-Johnson.
**             Après cette étape, la main chain est triée.
**             Le premier "pend" (partenaire du plus petit de la main chain)
**             est déjà < que son partenaire → on l'insère en tête.
**
**   Phase 3 — Insérer les "pends" dans la main chain par BINARY SEARCH,
**             dans l'ordre dicté par les NOMBRES DE JACOBSTHAL.
**             Cet ordre garantit que chaque insertion a au maximum
**             une puissance de 2 comme borne supérieure → comparaisons minimales.
**
** NOMBRES DE JACOBSTHAL : 0, 1, 1, 3, 5, 11, 21, 43, 85, 171, ...
** Formule : J(n) = J(n-1) + 2*J(n-2), avec J(0)=0, J(1)=1
** On insère d'abord le pend à l'index J(k), puis J(k)-1, J(k)-2, ...
** jusqu'au pend suivant J(k-1), toujours dans l'ordre décroissant.
*/

class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        // Lance le tri et affiche les résultats + temps pour les deux conteneurs
        void sort(int argc, char* argv[]);

    private:
        // ---- Implémentation avec std::vector ----
        void _sortVector(std::vector<int>& v);
        void _fordJohnsonVector(std::vector<int>& v);
        size_t _binarySearchVector(const std::vector<int>& v, int val, size_t end) const;

        // ---- Implémentation avec std::deque ----
        void _sortDeque(std::deque<int>& d);
        void _fordJohnsonDeque(std::deque<int>& d);
        size_t _binarySearchDeque(const std::deque<int>& d, int val, size_t end) const;

        // Génère la suite de Jacobsthal jusqu'à n
        std::vector<size_t> _jacobsthal(size_t n) const;
};

#endif
