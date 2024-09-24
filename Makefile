NAME = minishell
CC = cc
C_FLAGS = -Wall -Wextra -Werror -fPIE
I_FLAGS = -Iinclude/ -Ilibft/ -Iprintf/
H_FLAGS = -lreadline -lft -lftprintf
L_FLAGS = -Llibft -Lprintf #-lft

LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

FLAGS = $(C_FLAGS) $(I_FLAGS)
LINK_FLAGS = $(L_FLAGS) $(H_FLAGS)

SRCDIR = ./src
LEXERDIR = ./src/lexer
PARSERDIR = ./src/parser
REDIRECTDIR = ./src/redirect
BUILTINDIR = ./src/builtin
OBJDIR = ./obj

SRCS =	$(addprefix $(SRCDIR)/,$(FILES))\
		$(addprefix $(LEXERDIR)/, $(LEXER_FILES))\
		$(addprefix $(PARSERDIR)/, $(PARSER_FILES)) \
		$(addprefix $(REDIRECTDIR)/, $(REDIRECT_FILES)) \
		$(addprefix $(BUILTINDIR)/, $(BUILTIN_FILES))

OBJS = $(addprefix $(OBJDIR)/, $(FILES:.c=.o)) \
       $(addprefix $(OBJDIR)/, $(LEXER_FILES:.c=.o)) \
       $(addprefix $(OBJDIR)/, $(PARSER_FILES:.c=.o)) \
	   $(addprefix $(OBJDIR)/, $(REDIRECT_FILES:.c=.o)) \
	   $(addprefix $(OBJDIR)/, $(BUILTIN_FILES:.c=.o))

FILES = main.c env.c error.c env_utils.c
LEXER_FILES = lexer_main.c operator.c print_token.c quote.c token_bool.c token.c word.c expansion.c expansion_env.c expansion_utils.c expansion_split.c expansion_split_utils.c expansion_bool.c expansion_token_bool.c
PARSER_FILES = parser_main.c parser_bool.c parser_utils.c print_parser.c parser_command.c
#add
REDIRECT_FILES = $(notdir $(wildcard $(REDIRECTDIR)/*.c))
BUILTIN_FILES = $(notdir $(wildcard $(BUILTINDIR)/*.c))


all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJS)  
	$(CC) $(FLAGS) $(OBJS) -o $@ $(LINK_FLAGS)

$(LIBFT):
	make -C libft/

$(PRINTF):
	make -C printf/


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(LEXERDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(PARSERDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(REDIRECTDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(BUILTINDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C libft/ clean
	make -C printf/ clean

fclean: clean
	$(RM) $(NAME)
	make -C libft/ fclean
	make -C printf/ fclean

re: fclean all

debug: re
debug: C_FLAGS = -g -fsanitize=address
debug: FLAGS = $(C_FLAGS) $(I_FLAGS) $(H_FLAGS)
