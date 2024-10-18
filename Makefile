NAME = minishell
CC = cc
C_FLAGS = -Wall -Wextra -Werror -fPIE
I_FLAGS = -Iinclude/ -Ilibft/ -Iprintf/
H_FLAGS = -lreadline -lft -lftprintf
L_FLAGS = -Llibft -Lprintf

LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

FLAGS = $(C_FLAGS) $(I_FLAGS)
LINK_FLAGS = $(L_FLAGS) $(H_FLAGS)

SRCDIR = ./src
LEXERDIR = ./src/lexer
PARSERDIR = ./src/parser
REDIRECTDIR = ./src/redirect
BUILTINDIR = ./src/builtin
SIGNALDIR = ./src/signal
OBJDIR = ./obj

LEXER_FILES = 	lexer.c \
				lexer_word.c \
				lexer_token.c \
				lexer_quote.c \
				lexer_operator.c \
				lexer_error.c \
				lexer_bool.c \
				lexer_check.c \
				expansion.c \
				expansion_utils.c \
				expansion_env.c \
				expansion_bool.c

PARSER_FILES =	parser_main.c \
				parser_utils.c \
				parser_command.c \
				parser_bool.c \

REDIRECT_FILES = heredoc_expansion.c \
					heredoc_expansion_utils.c \
					heredoc_utils.c \
					heredoc.c \
					pipe_error.c \
					pipe_heredoc.c \
					pipe_struct_init.c \
					pipe_utils.c \
					pipe.c \
					no_pipe.c \
					redirect_error.c \
					redirect_input.c \
					redirect_output.c \
					redirect_utils.c \
					redirect_builtin.c \
					redirect.c

SIGNAL_FILES = signal.c \
				signal_handler.c

BUILTIN_FILES =	builtin_bash.c \
				builtin_minishell.c \
				cd_builtin.c \
				echo_builtin.c \
				env_builtin.c \
				exec_main.c \
				export_builtin.c \
				export_builtin_utils.c \
				pwd_builtin.c \
				unset_builtin.c \
				exit_builtin.c \
				exit_builtin_utils.c \
				builtin_bash_utils.c

FILES =	main.c \
		env.c \
		env_utils.c \
		free_env.c \
		free_all.c \
		free_parser.c \
		error.c

SRCS =	$(addprefix $(SRCDIR)/,$(FILES))\
		$(addprefix $(LEXERDIR)/, $(LEXER_FILES))\
		$(addprefix $(PARSERDIR)/, $(PARSER_FILES)) \
		$(addprefix $(REDIRECTDIR)/, $(REDIRECT_FILES)) \
		$(addprefix $(BUILTINDIR)/, $(BUILTIN_FILES)) \
		$(addprefix $(SIGNALDIR)/, $(SIGNAL_FILES))

OBJS = $(addprefix $(OBJDIR)/, $(FILES:.c=.o)) \
       $(addprefix $(OBJDIR)/, $(LEXER_FILES:.c=.o)) \
       $(addprefix $(OBJDIR)/, $(PARSER_FILES:.c=.o)) \
	   $(addprefix $(OBJDIR)/, $(REDIRECT_FILES:.c=.o)) \
	   $(addprefix $(OBJDIR)/, $(BUILTIN_FILES:.c=.o)) \
	   $(addprefix $(OBJDIR)/, $(SIGNAL_FILES:.c=.o))

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

$(OBJDIR)/%.o: $(SIGNALDIR)/%.c
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
