/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:50:29 by hakobaya          #+#    #+#             */
/*   Updated: 2024/02/16 17:07:56 by hakobaya         ###   ########.fr       */
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
	int				type;
	char			*data;
}				t_token;

//next, prevで前後のトークン、タイプは後々int型ではなく新たな構造体か何かを宣言する。
//typeにはword, semicoron, pipeなどが入る、マクロかなんかで設定してもいいかもしれない
// #define PIPE 1 など
//dataには入力値をのままを格納する

#endif