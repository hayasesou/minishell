/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:50:29 by hakobaya          #+#    #+#             */
/*   Updated: 2024/03/07 23:05:34 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>

//enum列挙型
typedef enum e_token_type {
	CHAR,
	PIPE,
	QUOTE,
	CHAR_QUOTE,
	D_QUOTE,
	CHAR_D_QUOTE,
	GREATER,
	D_GREATER, // redirect
	LESSER,
	D_LESSER, // heredoc
	SEMICOLON,
	SPACE,
	TAB,
	IO_NUM,
	ESCAPE, // いる？
	//COMMAND
}			t_token_type;

typedef enum e_token_state {
	IN_D_QUOTE,
	IN_QUOTE,
	GENERAL
}			t_token_state;

typedef struct s_token	t_token;

struct	s_token {
	char 			*data;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
};

typedef struct s_env t_env;

struct s_env {
	char	**line;
	t_env	*next;
	t_env	*prev;
};

typedef struct s_context t_context;

struct s_context {
	// 構造体の総まとめをこの構造体にまとめる
};

#endif