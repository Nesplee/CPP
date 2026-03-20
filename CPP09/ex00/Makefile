# **************************************************************************** #
#                                                                              #
#   Makefile                                         C++ Module 09 - STL       #
#   ex00 : Bitcoin Exchange                                                    #
#                                                                              #
#   CONCEPT : Variables Makefile                                               #
#   NAME     = nom du binaire final                                            #
#   CXX      = compilateur C++                                                 #
#   CXXFLAGS = options de compilation (obligatoires selon le sujet)            #
#   SRCS     = liste des fichiers source                                       #
#   OBJS     = fichiers objets (.o) générés depuis les .cpp                    #
#                                                                              #
# **************************************************************************** #

NAME     = btc
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS     = main.cpp BitcoinExchange.cpp
OBJS     = $(SRCS:.cpp=.o)

# Règle par défaut : compiler le projet
all: $(NAME)

# Règle de liaison : produit le binaire à partir des .o
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

# Règle de compilation : chaque .o dépend de son .cpp et du header
%.o: %.cpp BitcoinExchange.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Supprime les fichiers objets
clean:
	rm -f $(OBJS)

# Supprime tout (objets + binaire)
fclean: clean
	rm -f $(NAME)

# Recompile tout depuis zéro
re: fclean all

# CONCEPT : .PHONY
# Déclare des cibles "virtuelles" qui ne correspondent pas à de vrais fichiers.
# Sans ça, si un fichier "clean" existait dans le dossier, make ne lancerait
# pas la règle clean (il penserait que la cible est déjà à jour).
.PHONY: all clean fclean re
