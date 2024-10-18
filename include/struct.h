
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

typedef enum e_token_type {
    TK_WORD,
	TK_SPACE_WORD,
    TK_SINGLE_QUOTE,
	TK_SPACE_SINGLE_QUOTE,
    TK_DOUBLE_QUOTE,
	TK_SPACE_DOUBLE_QUOTE,
    TK_PIPE,
    TK_REDIR_IN,
    TK_REDIR_OUT,
    TK_REDIR_APPEND,
    TK_REDIR_HEREDOC,
	TK_EMPTY,
	TK_ERROR,
    TK_EOF
} t_token_type;

typedef struct s_expantion_info
{
	char *before_env;
	char *after_env;
	char *env_name;
	char *line;
} t_expantion_info;


typedef struct s_token {
	char			*data;
	t_token_type	type;
	bool			space_before;
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
	char				*filename;
	t_redirect_type		type;
	t_file				*next;
	int heredoc_fd; //仮に追加
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
	t_token     *token_head;
	t_parser    *parser_head;
	t_env	    *env_head;
	int		    exit_status;
	bool	    sys_error;
}	t_context;

#endif
