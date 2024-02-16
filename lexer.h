/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:50:29 by hakobaya          #+#    #+#             */
/*   Updated: 2024/02/16 20:13:43 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>

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
	E_ASTERISK, //*
	E_AT, //@
	E_SHARP, //#
	E_HATENA, //?
	E_HYPHEN, //-
	E_DOLLAR, //$
	E_EXCLAMATION, //!
	E_ZERO, //($0) シェルまたはシェル スクリプトの名前に展開される
	E_COLON,
	E_PERIOD,
	E_BREAK,
	E_CD,
	E_CONTINUE,
	E_EVAL,
	E_EXEC,
	E_EXIT,
	E_EXPORT,
	E_GETOPTS,
	E_HASH,
	E_PWD,
	E_READONLY,
	E_RETURN,
	E_TEST,
	E_TIMES,
	E_TRAP,
	E_UMASK,
	E_UNSET,
	E_SEMICOLON,
	E_PIPE,
	E_STRING,
}			t_token_type;
//今後足していく、GNU bash manual 4.1ビルトイン関数の部分参照

#endif