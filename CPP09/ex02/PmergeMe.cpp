/* ************************************************************************** */
/*                                                                            */
/*   PmergeMe.cpp                                 C++ Module 09 - STL         */
/*   ex02 : PmergeMe — Ford-Johnson merge-insert sort                         */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>      // std::istringstream
#include <stdexcept>    // std::runtime_error
#include <ctime>        // clock()
#include <algorithm>    // std::swap, std::min

/* ==========================================================================
**  FORME CANONIQUE
** ========================================================================== */

PmergeMe::PmergeMe()  {}
PmergeMe::PmergeMe(const PmergeMe& o) { (void)o; }
PmergeMe& PmergeMe::operator=(const PmergeMe& o) { (void)o; return *this; }
PmergeMe::~PmergeMe() {}

/* ==========================================================================
**  _jacobsthal : génère les "fins de groupes" pour l'insertion Jacobsthal
**
**  CONCEPT : NOMBRES DE JACOBSTHAL ET ORDRE D'INSERTION
**  ------------------------------------------------------
**  Après avoir inséré pends[0] en tête de mainChain, on insère les pends
**  restants par groupes dans cet ordre :
**
**    Groupe 1 : pends[1]              → 1 élément
**    Groupe 2 : pends[3], pends[2]    → 2 éléments (de 3 vers 2)
**    Groupe 3 : pends[5], pends[4]    → 2 éléments
**    Groupe 4 : pends[11],...,pends[6] → 6 éléments
**    ...
**
**  Les "fins de groupes" sont : 1, 3, 5, 11, 21, 43, ...
**  Formule : t(1)=1, t(2)=3, t(k) = t(k-1) + 2*t(k-2)
**
**  POURQUOI CET ORDRE ?
**  Quand on insère pends[k], la mainChain contient exactement 2^j éléments
**  depuis la dernière fin de groupe. La recherche binaire dans 2^j éléments
**  fait exactement j comparaisons. C'est l'optimum théorique.
**
**  Cette fonction retourne le vecteur des fins de groupes ≤ n.
** ========================================================================== */
std::vector<size_t> PmergeMe::_jacobsthal(size_t n) const
{
    std::vector<size_t> seq;
    if (n == 0) return seq;

    size_t t0 = 1;   // Première fin de groupe
    size_t t1 = 3;   // Deuxième fin de groupe
    seq.push_back(t0);  // Toujours insérer le groupe finissant à l'indice 1

    while (t1 <= n)
    {
        seq.push_back(t1);
        size_t next = t1 + 2 * t0;
        t0 = t1;
        t1 = next;
    }
    // Si n n'est pas encore couvert (n > dernier groupe), ajouter n
    if (seq.back() < n)
        seq.push_back(n);

    return seq;
}

/* ==========================================================================
**  _insertionSortBySecond : tri par insertion sur vecteur de paires
**  Trie les paires par leur SECOND élément (le "grand" de la paire).
**
**  CONCEPT : TRI PAR INSERTION
**  ----------------------------
**  On maintient une partie gauche triée et on insère chaque nouvel élément
**  au bon endroit. Complexité O(n²) mais très efficace pour les petits n
**  ou les tableaux presque triés — ce qui est notre cas ici.
**
**  On utilise cette fonction plutôt que std::sort pour ne pas dépendre
**  de l'algorithme générique (<algorithm> est autorisé dans ce module,
**  mais écrire notre propre sort montre qu'on comprend le mécanisme).
** ========================================================================== */
static void insertionSortBySecond(std::vector<std::pair<int,int> >& pairs)
{
    for (size_t i = 1; i < pairs.size(); ++i)
    {
        std::pair<int,int> key = pairs[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && pairs[j].second > key.second)
        {
            pairs[j + 1] = pairs[j];
            --j;
        }
        pairs[j + 1] = key;
    }
}

/* ============================================================================
**
**   VECTEUR — Ford-Johnson
**
** ========================================================================== */

/*
** _binarySearchVector : retourne la position d'insertion de 'val' dans v[0..end-1]
**
** CONCEPT : RECHERCHE BINAIRE
** ----------------------------
** Principe : à chaque étape, on divise l'espace de recherche par 2.
**   - si v[mid] <= val → val est dans la moitié droite → lo = mid+1
**   - si v[mid] > val  → val est dans la moitié gauche → hi = mid
** À la fin, lo == hi == position d'insertion.
**
** Complexité : O(log n). Pour 3000 éléments : ~12 comparaisons max.
** Pour 1 milliard d'éléments : ~30 comparaisons. C'est la magie du log !
*/
size_t PmergeMe::_binarySearchVector(const std::vector<int>& v, int val, size_t end) const
{
    size_t lo = 0, hi = end;
    while (lo < hi)
    {
        size_t mid = lo + (hi - lo) / 2;  // Évite le dépassement de (lo+hi)/2
        if (v[mid] <= val)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

/*
** _fordJohnsonVector : algorithme Ford-Johnson récursif sur std::vector
**
** CONCEPT : RÉCURSION ET INVARIANT
** ---------------------------------
** L'invariant de cette fonction : à la fin, v est trié en ordre croissant.
** À chaque appel récursif sur la mainChain, l'invariant tient.
** Donc quand on revient du récursif, mainChain est triée → on peut faire
** des recherches binaires efficaces pour insérer les pends.
**
** COMPLEXITÉ : O(n log n) comparaisons — optimal pour un tri par comparaison.
** Ford-Johnson est même "optimal" au sens du nombre MINIMUM de comparaisons
** pour certaines valeurs de n (en-dessous de la borne inférieure log₂(n!)).
*/
void PmergeMe::_fordJohnsonVector(std::vector<int>& v)
{
    size_t n = v.size();
    if (n <= 1) return;

    /* -----------------------------------------------------------------------
    **  PHASE 1 : Trier chaque paire adjacente
    **
    **  On garantit v[2i] <= v[2i+1] pour tout i valide.
    **  Une comparaison par paire = n/2 comparaisons totales.
    ** --------------------------------------------------------------------- */
    for (size_t i = 0; i + 1 < n; i += 2)
        if (v[i] > v[i + 1])
            std::swap(v[i], v[i + 1]);

    // Sauvegarder l'élément orphelin si n est impair
    bool hasOdd = (n % 2 != 0);
    int  oddElem = hasOdd ? v[n - 1] : 0;

    /* -----------------------------------------------------------------------
    **  PHASE 2 : Construire les paires (petit, grand) et trier récursivement
    **
    **  On extrait les "grands" de chaque paire, on les trie récursivement
    **  avec Ford-Johnson, puis on reconstruit la correspondance (petit↔grand)
    **  en retriant les paires par leur grand élément.
    **
    **  POURQUOI LE TRI DES PAIRES ?
    **  Après _fordJohnsonVector(larges), larges est trié.
    **  Pour savoir quel "petit" correspond à quel "grand" dans cet ordre,
    **  on trie les paires originales par leur second élément (tri stable).
    **  Ainsi pairs[i].first = le pendant du grand larges[i].
    ** --------------------------------------------------------------------- */
    std::vector<std::pair<int,int> > pairs;
    for (size_t i = 0; i + 1 < n; i += 2)
        pairs.push_back(std::make_pair(v[i], v[i + 1]));
        // v[i] <= v[i+1] grâce à la phase 1

    // Extraire les grands et les trier récursivement
    std::vector<int> larges;
    for (size_t i = 0; i < pairs.size(); ++i)
        larges.push_back(pairs[i].second);
    _fordJohnsonVector(larges);  // Récursion !

    // Retrier les paires par leur second élément pour retrouver
    // la correspondance (petit ↔ grand trié)
    insertionSortBySecond(pairs);
    // Maintenant pairs[i].second == larges[i] pour tout i

    /* -----------------------------------------------------------------------
    **  PHASE 3 : Construire mainChain et insérer les pends
    **
    **  mainChain commence avec les grands (déjà triés).
    **  On insère d'abord pends[0] en tête (il est <= larges[0] par définition).
    **  Puis on insère les pends restants dans l'ordre de Jacobsthal via
    **  recherche binaire.
    ** --------------------------------------------------------------------- */
    std::vector<int> mainChain = larges;
    std::vector<int> pends;
    for (size_t i = 0; i < pairs.size(); ++i)
        pends.push_back(pairs[i].first);

    // pends[0] <= larges[0] car ils étaient une paire → insertion en tête
    mainChain.insert(mainChain.begin(), pends[0]);

    // Insérer pends[1..m-1] dans l'ordre de Jacobsthal
    size_t numPends = pends.size();
    if (numPends > 1)
    {
        std::vector<size_t> jSeq = _jacobsthal(numPends - 1);
        size_t prev = 0;

        for (size_t k = 0; k < jSeq.size(); ++k)
        {
            size_t curr = std::min(jSeq[k], numPends - 1);

            // Insérer de curr vers prev+1 (ordre décroissant dans le groupe)
            for (size_t idx = curr; idx > prev; --idx)
            {
                /*
                ** BORNE DE RECHERCHE BINAIRE :
                ** pends[idx] est le pendant de larges[idx-1].
                ** Comme larges[idx-1] >= pends[idx], la position d'insertion
                ** de pends[idx] est forcément ≤ position de larges[idx-1] dans mainChain.
                ** On cherche dans tout mainChain pour simplifier (correct mais
                ** légèrement sous-optimal en nombre de comparaisons).
                */
                size_t pos = _binarySearchVector(mainChain, pends[idx], mainChain.size());
                mainChain.insert(mainChain.begin() + pos, pends[idx]);
            }
            prev = curr;
        }
    }

    // Insérer l'élément orphelin s'il existe
    if (hasOdd)
    {
        size_t pos = _binarySearchVector(mainChain, oddElem, mainChain.size());
        mainChain.insert(mainChain.begin() + pos, oddElem);
    }

    v = mainChain;
}

void PmergeMe::_sortVector(std::vector<int>& v)
{
    _fordJohnsonVector(v);
}

/* ============================================================================
**
**   DEQUE — même algorithme, conteneur différent
**
**  CONCEPT : POURQUOI std::deque EST PLUS LENT QUE std::vector ?
**  ---------------------------------------------------------------
**  std::vector : mémoire CONTIGÜE → excellent cache locality
**    CPU lit en cache des blocs de 64 octets (cache lines)
**    → accéder à v[i] charge aussi v[i+1], v[i+2]... déjà en cache
**
**  std::deque : mémoire allouée par BLOCS non contigus
**    Chaque accès d[i] nécessite : trouver le bon bloc, puis l'offset
**    → double indirection → moins efficace pour le cache CPU
**
**  Pour 3000 éléments, la différence est visible (x3 à x10 plus lent).
**  C'est pourquoi le sujet demande de mesurer et comparer les deux.
**
** ========================================================================== */

size_t PmergeMe::_binarySearchDeque(const std::deque<int>& d, int val, size_t end) const
{
    size_t lo = 0, hi = end;
    while (lo < hi)
    {
        size_t mid = lo + (hi - lo) / 2;
        if (d[mid] <= val)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

static void insertionSortBySecondDeque(std::vector<std::pair<int,int> >& pairs)
{
    for (size_t i = 1; i < pairs.size(); ++i)
    {
        std::pair<int,int> key = pairs[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && pairs[j].second > key.second)
        {
            pairs[j + 1] = pairs[j];
            --j;
        }
        pairs[j + 1] = key;
    }
}

void PmergeMe::_fordJohnsonDeque(std::deque<int>& d)
{
    size_t n = d.size();
    if (n <= 1) return;

    // Phase 1 : Trier les paires
    for (size_t i = 0; i + 1 < n; i += 2)
        if (d[i] > d[i + 1])
            std::swap(d[i], d[i + 1]);

    bool hasOdd = (n % 2 != 0);
    int  oddElem = hasOdd ? d[n - 1] : 0;

    // Phase 2 : Paires + récursion
    std::vector<std::pair<int,int> > pairs;
    for (size_t i = 0; i + 1 < n; i += 2)
        pairs.push_back(std::make_pair(d[i], d[i + 1]));

    // Trier les grands récursivement (via deque)
    std::deque<int> largesDeq;
    for (size_t i = 0; i < pairs.size(); ++i)
        largesDeq.push_back(pairs[i].second);
    _fordJohnsonDeque(largesDeq);

    // Retrouver la correspondance
    insertionSortBySecondDeque(pairs);

    // Phase 3 : Construire mainChain et insérer
    std::deque<int> mainChain(largesDeq);
    std::vector<int> pends;
    for (size_t i = 0; i < pairs.size(); ++i)
        pends.push_back(pairs[i].first);

    mainChain.insert(mainChain.begin(), pends[0]);

    size_t numPends = pends.size();
    if (numPends > 1)
    {
        std::vector<size_t> jSeq = _jacobsthal(numPends - 1);
        size_t prev = 0;

        for (size_t k = 0; k < jSeq.size(); ++k)
        {
            size_t curr = std::min(jSeq[k], numPends - 1);
            for (size_t idx = curr; idx > prev; --idx)
            {
                size_t pos = _binarySearchDeque(mainChain, pends[idx], mainChain.size());
                mainChain.insert(mainChain.begin() + pos, pends[idx]);
            }
            prev = curr;
        }
    }

    if (hasOdd)
    {
        size_t pos = _binarySearchDeque(mainChain, oddElem, mainChain.size());
        mainChain.insert(mainChain.begin() + pos, oddElem);
    }

    d = mainChain;
}

void PmergeMe::_sortDeque(std::deque<int>& d)
{
    _fordJohnsonDeque(d);
}

/* ==========================================================================
**  sort : point d'entrée principal
**
**  CONCEPT : clock() pour mesurer le temps CPU
**  --------------------------------------------
**  CLOCKS_PER_SEC : nombre de "ticks" CPU par seconde (au moins 1000000)
**  (double)(end - start) / CLOCKS_PER_SEC * 1e6 → microsecondes
**
**  Attention : clock() mesure le temps CPU consommé par le processus,
**  pas le temps réel (wall clock). Si le OS préempte le processus,
**  clock() ne compte pas ce temps d'attente.
** ========================================================================== */
void PmergeMe::sort(int argc, char* argv[])
{
    std::vector<int> vec;
    std::deque<int>  deq;

    for (int i = 1; i < argc; ++i)
    {
        std::istringstream iss(argv[i]);
        int val;
        if (!(iss >> val) || val < 0)
            throw std::runtime_error("Error");
        std::string rest;
        if (iss >> rest)
            throw std::runtime_error("Error");
        vec.push_back(val);
        deq.push_back(val);
    }

    if (vec.empty())
        throw std::runtime_error("Error");

    // Afficher avant
    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i > 0) std::cout << " ";
        std::cout << vec[i];
    }
    std::cout << std::endl;

    // Trier et mesurer std::vector
    clock_t startVec = clock();
    _sortVector(vec);
    clock_t endVec = clock();

    // Trier et mesurer std::deque
    clock_t startDeq = clock();
    _sortDeque(deq);
    clock_t endDeq = clock();

    // Afficher après
    std::cout << "After:  ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i > 0) std::cout << " ";
        std::cout << vec[i];
    }
    std::cout << std::endl;

    double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1e6;
    double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1e6;

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size()
              << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}
