NAME = client
CXX = c++
CXXFLAGS = -g -Wall -Wextra -Werror -I../../../

OBJROOT = ../../../obj/src/bonus/crypt

all: $(NAME)

$(NAME): $(OBJROOT)/client.o $(OBJROOT)/cryp.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJROOT)/client.o: ../../client.cpp
	@mkdir -p $(OBJROOT)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJROOT)/cryp.o: cryp.cpp
	@mkdir -p $(OBJROOT)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJROOT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re