NAME = client
CC = c++
CFLAGS = -g -Wall -Wextra -Werror -I../../../

OBJROOT = ../../../obj/src/bonus/crypt

SRC = ../../client.cpp \
	cryp.cpp

OBJ = $(SRC:%.cpp=$(OBJROOT)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJROOT)/%.o: %.cpp
	@mkdir -p $(OBJROOT)
	$(CC) $(CFLAGS) -c $< -o $(OBJROOT)/$(notdir $@)

clean:
	rm -rf $(OBJROOT)

fclean: clean
	rm -f $(NAME)

re: fclean all
