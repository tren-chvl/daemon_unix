NAME = Ben_AFK
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -I../../../

OBJDIR = ../../../obj/src/bonus/cli_grah

SRC = ben_afk.cpp \
	  ../crypt/cryp.cpp

OBJ = $(OBJDIR)/ben_afk.o \
	  $(OBJDIR)/cryp.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -lncurses -o $(NAME)

$(OBJDIR)/ben_afk.o: ben_afk.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/cryp.o: ../crypt/cryp.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re