
#ifndef LEXER_H
# define LEXER_H

# include "struct.h"

# include <readline/readline.h>
# include <readline/history.h>

t_token	*add_token(t_token_type type, t_token *cur, char *data);
t_token	*tokenize(char *line);

#endif