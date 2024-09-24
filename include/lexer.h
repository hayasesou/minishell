
#ifndef LEXER_H
# define LEXER_H

# include "struct.h"
# include "minishell.h"

# include <readline/readline.h>
# include <readline/history.h>

// bool

bool	        is_blank(char c);
bool	        is_word(char c);
bool	        is_quote(char c);
bool        	is_operator(char c);
bool	        is_single_quote(char c);
bool	        is_double_quote(char c);
bool	        is_single_quote_closed(char *line);
bool	        is_double_quote_closed(char *line);

// word
bool        	consume_blank(char **line_ptr, char *line);
void            word(char **line_ptr, char *line, t_token *token, bool space_before);

// operator
void            operator(char **line_ptr, char *line, t_token *token);
char	        *select_op(char *line);
t_token_type	select_op_type(char *op);

// quote
void            quote(char **line_ptr, char *line, t_token *token, bool space_before);
char            *single_quote_removal(char *str);
char            *double_quote_removal(char *str);
bool            is_combinable(t_token *token);

// token
t_token         *token_node_create(char *data, t_token_type type);
void        	token_node_add(t_token *head, t_token *new_token);
t_token     	*token_init(t_context *ctx);
void        	free_tokens(t_token *token);

// expansion
void            expansion(t_token *token_head, t_context *ctx);
char	        *ft_strjoin_free(char *s1, char *s2);
t_token         *expansion_split(t_token *node);

// expansion_env
void            expansion_env(char *data, t_token *token, size_t *i, t_context *ctx);

// expansion_utils
char            *ft_strjoin_all(char *s1, char *s2, char *s3);
char            *ft_strjoin_free(char *s1, char *s2);
void            free_result(char **result, size_t i);

// expansion_split
t_token         *expansion_split(t_token *node);
char            **ft_split_charset(char *s, char *charset);

// expansion_bool
bool            is_env_name(char c);
bool            is_heredoc_expansion(t_token *token);
bool            is_env_name_start(char c);
bool            is_env_name_char(char c);
bool            is_charset(char c, const char *charset);
bool            is_double_quote_expansion(t_token_type type);
bool            is_word_expansion(t_token_type type);

// main
void        	lexer(t_context *ctx, char *line);
void	        print_lexer(t_token *token_head);

#endif