# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

C++ Module 09 — STL. Three exercises exploiting the C++ Standard Template Library containers and algorithms. Standard: **C++98** strictly (`-std=c++98`).

## Build Commands

Each exercise lives in its own directory (`ex00/`, `ex01/`, `ex02/`) with its own Makefile.

```sh
# Dans un répertoire d'exercice :
make          # compile (équivalent à make all)
make clean    # supprime les .o
make fclean   # supprime les .o et le binaire
make re       # fclean + all
```

Compilation flags obligatoires : `-Wall -Wextra -Werror`. Le Makefile doit utiliser `c++` et **ne pas relinker**.

## Critical Module Rule — Container Uniqueness

**Each STL container type can only be used in ONE exercise across the entire module.**
Plan container assignments before coding:
- `ex00` (btc) — e.g. `std::map`
- `ex01` (RPN) — e.g. `std::stack`
- `ex02` (PmergeMe) — must use **two different** containers not used before (e.g. `std::vector` + `std::deque`)

Once a container is used in an exercise, it is forbidden in all subsequent exercises.

## Language & Style Constraints

- C++98 only — no C++11 or later, no Boost
- STL containers (`vector`, `list`, `map`, etc.) and `<algorithm>` are **allowed** (this is Modules 08 & 09)
- Forbidden: `using namespace <ns>`, `friend` keyword, `*printf()`, `*alloc()`, `free()`
- Classes must follow **Orthodox Canonical Form** (default ctor, copy ctor, copy assignment op, destructor)
- No function implementation in header files (except templates)
- All headers must have include guards
- Class names in UpperCamelCase; files named after their class

## Exercises

### ex00 — Bitcoin Exchange (`btc`)
- Files: `Makefile`, `main.cpp`, `BitcoinExchange.{cpp,hpp}`
- Reads a CSV database (`data.csv`) of bitcoin prices over time
- Takes an input file argument with lines `"date | value"` (date: YYYY-MM-DD, value: float/int 0–1000)
- For each input line, finds the closest **lower or equal** date in the DB and outputs `date => value = result`
- Error cases: bad date format, negative value, value > 1000, missing date in DB

### ex01 — Reverse Polish Notation (`RPN`)
- Files: `Makefile`, `main.cpp`, `RPN.{cpp,hpp}`
- Takes a quoted RPN expression as a single argument: `./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"`
- Operands are single digits (< 10); operators: `+ - / *`
- Output result to stdout; errors to stderr as `"Error"`
- No brackets or decimal numbers in input

### ex02 — PmergeMe (`PmergeMe`)
- Files: `Makefile`, `main.cpp`, `PmergeMe.{cpp,hpp}`
- Takes a positive integer sequence as program arguments
- Implements the **Ford-Johnson merge-insert sort algorithm** (TAOCP Vol.3, p.184) on **two different containers**
- Must implement the algorithm separately for each container (no generic shared function)
- Output format:
  ```
  Before:  <unsorted sequence>
  After:   <sorted sequence>
  Time to process a range of N elements with std::[container1] : X us
  Time to process a range of N elements with std::[container2] : X us
  ```
- Must handle at least 3000 integers; errors to stderr

## Architecture Pattern

Each exercise follows this structure:
```
exNN/
├── Makefile
├── main.cpp          ← argument parsing + instantiation
├── ClassName.hpp     ← class declaration + include guard
└── ClassName.cpp     ← method implementations
```

`main.cpp` handles argument validation and delegates all logic to the class. The class encapsulates the container and exposes a minimal public interface.
