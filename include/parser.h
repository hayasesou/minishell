#ifndef PARSER_H
# define PARSER_H

// parser main

void    parser(t_context *ctx);
void    parser_pipe(t_parser **args);
void    command_init(t_parser *args);
void    create_command(t_parser *args, t_token *token);
void    file_node_add(char *filename, int type);
void    arg_node_create(t_parser **args, t_token *token);
t_parser    *args_init(void);
t_token    *cat_token(t_token *token);

// parser bool
bool    is_string(t_token *token);
bool    is_in_quote(t_token *token);
bool    is_redirect(t_token *token);
bool    is_pipe(t_token *token);
bool    is_cat_token(t_token *token);

// print parser
void	print_parser(t_parser *parser_head);
// static void	print_parser_file(t_file *file);
// static void	print_parser_type(t_redirect_type type);

#endif