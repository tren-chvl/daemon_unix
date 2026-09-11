NAME = Matt_daemon
CC = c++
CFLAGS = -g -Wall -Wextra -Werror -I.

OBJDIR = obj

SRC = src/main.cpp \
	src/daemon.cpp \
	src/server.cpp \
	src/report.cpp \
	src/signaux.cpp \
	src/bonus/crypt/cryp.cpp \
	src/bonus/remote_shell/re_shell.cpp \
	src/bonus/advance_log/log.cpp

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

all: $(NAME) client

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

client:
	make -C src/bonus/crypt

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	make -C src/bonus/crypt clean

fclean: clean
	rm -f $(NAME)
	make -C src/bonus/crypt fclean

re: fclean all

.PHONY: all clean fclean re client
