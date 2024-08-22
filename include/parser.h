#ifndef PARSER_H
# define PARSER_H

// parser main

void    parser(t_context *ctx);
void    create_command(t_parser *args, t_token *token);

// parser bool
bool    is_string(t_token *token);
bool    is_in_quote(t_token *token);
bool    is_redirect(t_token *token);
bool    is_pipe(t_token *token);
bool    is_cat_token(t_token *token);

// parser init
t_parser        *args_init(void);
void command_init(t_parser *args, t_token *token);
void            parser_pipe(t_parser **args);
t_redirect_type get_redirect_type(t_token_type type);
void            file_node_add(t_parser *args, char *filename, t_redirect_type type);

// parser token
t_token    *cat_token(t_token *token);
void        join_tokens(t_token **new_token, t_token **tmp);
void        join_words(t_token **new_token, t_token **tmp);
void        append_token(t_parser **args, t_token *token);
void        arg_node_create(t_parser **args, t_token *token);

// parser utils
t_parser *arg_node_add(t_parser *args);
char *ft_strjoin(const char *str1, const char *str2);


// print parser
void	print_parser(t_parser *parser_head);

#endif
