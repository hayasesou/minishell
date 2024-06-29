#ifndef STRUCT_TEST_H
# define STRUCT_TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <stdbool.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

// 前方宣言
typedef struct s_token t_token;
typedef struct s_ast t_ast;
typedef struct s_env t_env;

//enum列挙型
//typedef enum e_token_type {
//	CHAR,
//	PIPE,
//	QUOTE,
//	CHAR_QUOTE,
//	D_QUOTE,
//	CHAR_D_QUOTE,
//	GREATER,
//	D_GREATER, // redirect
//	LESSER,
//	D_LESSER, // heredoc
//	SEMICOLON,
//	SPACE,
//	TAB,
//	IO_NUM,
//	ESCAPE, // いる？
//	//COMMAND
//}			t_token_type;

typedef enum e_token_type {
	TK_REDIR_IN = 0,
	TK_REDIR_OUT = 1,
	TK_REDIR_APPEND = 2,
	TK_REDIR_HEREDOC = 3,
	TK_OP,
	TK_WORD,
	TK_PIPE,
	TK_EOF,
}	t_token_type;

//typedef enum e_token_state {
//	IN_D_QUOTE,
//	IN_QUOTE,
//	GENERAL
//}			t_token_state;


typedef struct s_token {
	char			*data;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
}	t_token;

typedef enum e_node_type {
	ND_CMD,
	ND_PIPE
}	t_node_type;

typedef struct s_redirect {
	char			*file;
	t_token_type	type;
}	t_redirect;

typedef struct s_list {
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_ast {
	t_node_type	type;
	t_token		*argv;
	t_list		*redir_lst;
	t_ast		*left;
	t_ast		*right;
	t_token		*lst;
}	t_ast;

typedef struct s_env {
	char	**line;
	t_env	*next;
	t_env	*prev;
}	t_env;

struct s_context {
	// 構造体の総まとめをこの構造体にまとめる
	t_token	*token;
	t_ast	*ast;
	t_env	*env;
	int		status;
	bool	sys_error;
	bool	include_quote;
}	t_context;


void	fatal_error(const char *msg);
t_token	*add_token(char *data, t_token_type type);
bool	is_blank(char c);
bool	consume_blank(char **line_ptr, char *line);
bool	start_with_operator(const char *s, const char *operator);
bool	is_operator(const char *s);
t_token	*operator(char **line_ptr, char *line);
bool	is_metacharacter(char c);
bool	is_word(const char *s);
t_token	*word(char **line_ptr, char *line);
t_token	*token_init(void);
t_token	*tokenize(char *line);
void	free_tokens(t_token *token);


#endif
