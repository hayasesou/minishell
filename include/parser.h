#ifndef PARSER_H
# define PARSER_H

// parser main

void            parser(t_context *ctx);
void            free_parser(t_parser **head);
t_parser        *args_init(void);
int             add_redirect(t_parser *cur_arg, t_token *token);

// parser bool
bool            is_string(t_token *token);
bool            is_not_space_string(t_token *token);
bool            is_redirect(t_token *token);
bool            is_pipe(t_token *token);

// parser utils
t_redirect_type get_redirect_type(t_token_type type);

// parser command
void            free_command(char **cmd);
int             add_command(t_parser *cur_arg, char *cmd_str);
void            create_command(t_parser *args, t_token *token);

// print parser
void            print_parser(t_parser *parser_head);

#endif
