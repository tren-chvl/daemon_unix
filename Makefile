NAME = Matt_daemon
CXX = c++
CXXFLAGS = -g -Wall -Wextra -Werror -I.

OBJDIR = obj

SRC = src/main.cpp \
	src/daemon.cpp \
	src/server.cpp \
	src/report.cpp \
	src/signaux.cpp \
	src/bonus/crypt/cryp.cpp \
	src/bonus/remote_shell/re_shell.cpp \
	src/bonus/advance_log/log.cpp \
	src/bonus/auth/auth.cpp

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

all: $(NAME) client ben_afk

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

client:
	$(MAKE) -C src/bonus/crypt

ben_afk:
	$(MAKE) -C src/bonus/cli_grah

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C src/bonus/crypt clean
	$(MAKE) -C src/bonus/cli_grah clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C src/bonus/crypt fclean
	$(MAKE) -C src/bonus/cli_grah fclean

re: fclean all

.PHONY: all clean fclean re client ben_afk