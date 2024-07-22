NAME = minishell
CC = cc
C_FLAGS = -Wall -Wextra -Werror
I_FLAGS = -Iinclude/
H_FLAGS = -lreadline

FLAGS = $(C_FLAGS) $(I_FLAGS) #$(H_FLAGS)


SRCDIR = ./src
LEXERDIR = ./src/lexer
OBJDIR = ./obj

SRCS = $(addprefix $(SRCDIR)/,$(FILES)) $(addprefix $(LEXERDIR)/, $(LEXER_FILES))
# OBJS = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJDIR)/, $(FILES:.c=.o)) $(addprefix $(OBJDIR)/, $(LEXER_FILES:.c=.o))

FILES = main.c env.c error.c
LEXER_FILES = lexer_main.c operator.c print_token.c quote.c token_bool.c token.c word.c

all: $(NAME)

# $(NAME): $(OBJS)
# 	$(CC) $(FLAGS) $(OBJS) -o $@ $(H_FLAGS)

# .c.o:
# 	$(CC) $(C_FLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@


$(OBJDIR)/%.o: $(LEXERDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@ $(H_FLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: re
debug: C_FLAGS = -g -fsanitize=address
debug: FLAGS = $(C_FLAGS) $(I_FLAGS) $(H_FLAGS)