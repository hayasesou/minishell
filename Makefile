NAME = minishell
CC = cc
C_FLAGS = -Wall -Wextra -Werror
I_FLAGS = -Iinclude/
H_FLAGS = -lreadline

FLAGS = $(C_FLAGS) $(I_FLAGS) #$(H_FLAGS)


SRCDIR = ./src
LEXERDIR = ./src/lexer
PARSERDIR = ./src/parser
OBJDIR = ./obj

SRCS =	$(addprefix $(SRCDIR)/,$(FILES))\
		$(addprefix $(LEXERDIR)/, $(LEXER_FILES))\
		$(addprefix $(PARSERDIR)/, $(PARSER_FILES))

OBJS = $(addprefix $(OBJDIR)/, $(FILES:.c=.o)) \
       $(addprefix $(OBJDIR)/, $(LEXER_FILES:.c=.o)) \
       $(addprefix $(OBJDIR)/, $(PARSER_FILES:.c=.o))

FILES = main.c env.c error.c
LEXER_FILES = lexer_main.c operator.c print_token.c quote.c token_bool.c token.c word.c
PARSER_FILES = parser_main.c parser_bool.c print_parser.c parser_help.c

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

$(OBJDIR)/%.o: $(PARSERDIR)/%.c
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