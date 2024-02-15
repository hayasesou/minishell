NAME = minishell
CC = cc
C_FLAGS = -Wall -Wextra -Werror
#F_FLAGS =
H_FLAGS = -lreadline
FLAGS = $(C_FLAGS) $(H_FLAGS)

SRCDIR = ./src
OBJDIR = ./obj

SRCS = $(addprefix $(SRCDIR)/,$(FILES))
OBJS = $(SRCS:.c=.o)

FILES = main.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: re
debug: C_FLAGS = -g -fsanitize=address