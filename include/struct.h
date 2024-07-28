
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
typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_file	t_file;
typedef struct s_parser	t_parser;


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
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APPEND,
	TK_REDIR_HEREDOC,

	TK_OP,
	TK_WORD,
	TK_PIPE,
	TK_EOF,
	TK_EMPTY,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE
}	t_token_type;

typedef enum e_token_state {
	GENERAL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_token_state;

typedef struct s_token {
	char			*data;
	t_token_type	type;
	t_token_state	state;
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

typedef enum e_redirect_type
{
	UNKNOWN,
	QUOTE_HEREDOC,
	HEREDOC,
	IN_FILE,
	OUT_FILE,
	APPEND
}						t_redirect_type;

typedef struct s_list {
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_file
{
	char				*file_name;
	t_redirect_type		type;
	t_file				*next;
}						t_file;

typedef struct s_parser
{
	char				**cmd; // execve のような実装にするため
	t_file				*file;
	t_parser			*next;
	t_parser			*prev;
}						t_parser;

typedef struct s_env {
	char	*env_name;
	char	*env_val;
	t_env	*next;
	t_env	*prev;
}	t_env;

typedef struct s_context {
	// 構造体の総まとめをこの構造体にまとめる
	t_token	*token_head;
	t_env	*env_head;
	int		exit_status;
	bool	sys_error; // 一応
}	t_context;


// void	fatal_error(const char *msg);
// t_token	*add_token(char *data, t_token_type type);
// bool	is_blank(char c);
// bool	consume_blank(char **line_ptr, char *line);
// bool	start_with_operator(const char *s, const char *operator);
// t_token	*operator(char **line_ptr, char *line);
// bool	is_metacharacter(char c);
// t_token	*word(char **line_ptr, char *line);
// t_token	*token_init(void);
// t_token	*tokenize(char *line);
// void	free_tokens(t_token *token);

#endif
