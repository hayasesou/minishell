
#ifndef LEXER_H
# define LEXER_H

# include "struct.h"
# include "minishell.h"

# include <readline/readline.h>
# include <readline/history.h>

void	token_node_add(t_token *head, t_token *new_token);
t_token	*token_node_create(char *data, t_token_type type, t_token_state state);
void	*lexer(t_context *ctx, char *line);
void	fatal_error(const char *msg);
bool	is_blank(char c);
bool	consume_blank(char **line_ptr, char *line);
bool	start_with_operator(const char *s, const char *operator);
t_token	*operator(char **line_ptr, char *line);
bool	is_metacharacter(char c);
bool	is_word(const char *s);
t_token	*word(char **line_ptr, char *line);
t_token	*token_init(t_context *ctx);
t_token	*tokenize(char *line);
void	free_tokens(t_token *token);
bool	is_operator(char c);

#endif