NAME = minishell
CC = cc
C_FLAGS = -Wall -Wextra -Werror -fPIE
I_FLAGS = -Iinclude/ -Ilibft/
H_FLAGS = -lreadline
L_FLAGS = -Llibft -lft

LIBFT = libft/libft.a

FLAGS = $(C_FLAGS) $(I_FLAGS) $(L_FLAGS) #$(H_FLAGS)


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
PARSER_FILES = parser_main.c parser_bool.c parser_init.c parser_token.c parser_utils.c print_parser.c

all: $(NAME)


$(NAME): $(LIBFT) $(OBJS)  
	$(CC) $(FLAGS) $(OBJS) -o $@ $(H_FLAGS)

$(LIBFT):
	make -C libft/


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
	make -C libft/ clean

fclean: clean
	$(RM) $(NAME)
	make -C libft/ fclean

re: fclean all

debug: re
debug: C_FLAGS = -g -fsanitize=address
debug: FLAGS = $(C_FLAGS) $(I_FLAGS) $(H_FLAGS)