/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:50:29 by hakobaya          #+#    #+#             */
/*   Updated: 2024/02/16 19:20:55 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

// readlineから読まれた入力値をtokenに格納するための構造体

typedef struct s_token {
	struct s_token	*next;
	struct s_token	*prev;
	t_token_type	type;
	char			*data;
}				t_token;

//next, prevで前後のトークン、タイプは後々int型ではなく新たな構造体か何かを宣言する。
//dataには入力値をのままを格納する

//enum列挙型
typedef enum e_token_type {
	PIPE,
	STRING,
	SEMICORON
}			t_token_type;
//今後足していく


#endif