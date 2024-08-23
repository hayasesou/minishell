#ifndef PARSER_H
# define PARSER_H

// parser main

void            parser(t_context *ctx);
void            add_command(t_parser *cur_arg, char *cmd_str);
void            create_command(t_parser *args, t_token *token);
t_parser        *args_init(void);

// parser bool
bool            is_string(t_token *token);
bool            is_space_string(t_token *token);
bool            is_redirect(t_token *token);
bool            is_pipe(t_token *token);

// parser utils
char            *ft_strjoin(const char *str1, const char *str2);
void            join_words(char **combined_str, t_token **tmp);
t_redirect_type get_redirect_type(t_token_type type);

// print parser
void            print_parser(t_parser *parser_head);

#endif
