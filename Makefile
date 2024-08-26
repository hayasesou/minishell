NAME = minishell
CC = cc
C_FLAGS = -Wall -Wextra -Werror -fPIE
I_FLAGS = -Iinclude/ -Ilibft/
# linkerの順番
#https://stackoverflow.com/questions/45135/why-does-the-order-in-which-libraries-are-linked-sometimes-cause-errors-in-gcc
H_FLAGS = -lreadline -lft
L_FLAGS = -Llibft #-lft

LIBFT = libft/libft.a

FLAGS = $(C_FLAGS) $(I_FLAGS)
LINK_FLAGS = $(L_FLAGS) $(H_FLAGS)

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
PARSER_FILES = parser_main.c parser_bool.c parser_utils.c print_parser.c parser_command.c

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)  
	$(CC) $(FLAGS) $(OBJS) -o $@ $(LINK_FLAGS)

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
