
#ifndef LEXER_H
# define LEXER_H

# include "struct.h"
# include "minishell.h"

# include <readline/readline.h>
# include <readline/history.h>


// bool

bool	        is_blank(char c);
bool	        is_word(const char *s);
bool	        is_quote(char c);
bool	        is_single_quote(char c);
bool	        is_double_quote(char c);
bool	        is_single_quote_closed(char *line);
bool	        is_double_quote_closed(char *line);
bool        	is_operator(char c);

// word
bool        	consume_blank(char **line_ptr, char *line);
void        	*word(char **line_ptr, char *line, t_token *token);

// operator
t_token	       *operator(char **line_ptr, char *line, t_token *token);
char	        *select_op(char *line);
t_token_type	*select_op_type(char *op);

// quote
void	        quote(char **line_ptr, char *line, t_token *token);
t_token         *single_quote_removal(char *str);
t_token	        *double_quote_removal(char *str);

// token
t_token     	*token_node_create(char *data, t_token_type type, t_token_state state);
void        	token_node_add(t_token *head, t_token *new_token);
t_token     	*token_init(t_context *ctx);
void        	free_tokens(t_token *token);

// main
void        	*lexer(t_context *ctx, char *line);

#endif