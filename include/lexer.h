/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:09:06 by hakobaya          #+#    #+#             */
/*   Updated: 2024/10/18 23:35:39 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "struct.h"
# include <readline/history.h>
# include <readline/readline.h>

// bool

bool			is_blank(char c);
bool			is_word(char c);
bool			is_quote(char c);
bool			is_operator(char c);
bool			is_single_quote(char c);
bool			is_double_quote(char c);
bool			is_single_quote_closed(char *line);
bool			is_double_quote_closed(char *line);

// word
bool			consume_blank(char **line_ptr, t_token *token);
void			word(char **line_ptr, char *line, t_token *token,
					bool space_before);

// operator
void			operator(char **line_ptr, char *line, t_token *token,
					t_context *ctx);
char			*select_op(char *line);
t_token_type	select_op_type(char *op);

// quote
void			quote(char **line_ptr, char *line, t_token *token,
					t_context *ctx);

// token
t_token			*token_node_create(char *data, t_token_type type);
void			token_node_add(t_token *head, t_token *new_token);
t_token			*token_init(t_context *ctx);
void			free_tokens(t_token *token);

// expansion
void			expansion(t_token *token_head, t_context *ctx);

// expansion_env
void			expansion_env(char *data, t_token *token, size_t *i,
					t_context *ctx);

// expansion_utils
char			*ft_strjoin_all(char *s1, char *s2, char *s3);

// expansion_bool
bool			is_env_name(char c);
bool			is_heredoc_expansion(t_token *token);
bool			is_env_name_start(char c);
bool			is_env_name_char(char c);
bool			is_charset(char c, const char *charset);
bool			is_double_quote_expansion(t_token_type type);
bool			is_word_expansion(t_token_type type);

// check
void			check_token_operation(t_context *ctx);


// error
void			syntax_error(char *msg, t_context *ctx);
void			syntax_error_operation(char *msg, t_context *ctx);
void			syntax_error_unexpected_token(char *unexpected_token,
					t_context *ctx);

// main
void			lexer(t_context *ctx, char *line);
void			print_lexer(t_token *token_head);

#endif