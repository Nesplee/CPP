# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Run

Chaque exercice a son propre `Makefile` avec les cibles standard :

```bash
cd ex00 && make          # Compile
./easyfind               # Exécute

cd ex01 && make
./span

cd ex02 && make
./mutantstack
```

Cibles disponibles : `all`, `clean`, `fclean`, `re`.

**Flags de compilation** : `-Wall -Wextra -Werror -std=c++98`

## Architecture

Projet pédagogique 42 sur les **templates C++98** et la **STL**.

### ex00 — `easyfind` (fonction template)
- `easyfind.hpp` : fonction template `easyfind<T>(container, value)` qui cherche un entier dans n'importe quel conteneur STL séquentiel via `std::find`. Lance `std::runtime_error` si absent.
- Header-only (template = implémentation dans le `.hpp`).

### ex01 — `Span` (classe avec méthode template)
- `Span.hpp/.cpp` : classe non-template qui stocke jusqu'à N entiers dans un `std::vector<int>`.
- Méthode template `addRange<Iterator>(begin, end)` dans le `.hpp` pour ajouter une plage d'éléments.
- `shortestSpan()` : plus petite différence entre deux éléments (tri + différences adjacentes).
- `longestSpan()` : `max - min`.

### ex02 — `MutantStack` (classe template héritant de STL)
- `MutantStack.hpp` : classe template qui hérite de `std::stack<T>` et expose `begin()`/`end()` en accédant au membre protégé `c` (le conteneur interne `std::deque<T>`).
- Header-only (template).
- Expose aussi `const_iterator` pour les objets `const`.

## Contraintes importantes

- Standard **C++98 uniquement** (pas de C++11 ou plus récent).
- Forme canonique orthodoxe obligatoire pour les classes (constructeur par défaut/copie, opérateur `=`, destructeur).
- Les implémentations de templates doivent rester dans les `.hpp`.
