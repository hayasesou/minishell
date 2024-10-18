# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pipe.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/19 00:37:20 by hakobaya          #+#    #+#              #
#    Updated: 2024/10/19 00:37:21 by hakobaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#現在のディレクトリ内の.c ファイルをすべて取得
pipe_files=$(ls *.c)
builtin_files=$(ls ../builtin/*.c)

# 必要なインクルードディレクトリを指定
Include="-I../../include -I../../libft"
LFALGS="-L../../libft -lft"
H_FLAGS="-lreadline"
C_FLAGS="-g -fsanitize=address"

# コンパイル
cc $C_FLAGS $pipe_files ../error.c ../env.c ../env_utils.c $builtin_files $Include $LFALGS -Wall -Werror -Wextra -o pipex $H_FLAGS

# # コンパイルが成功した場合のみ実行
# if [ $? -eq 0 ]; then
#     ./pipex ls ls
# else
#     echo "Compilation failed."
#     exit 1
# fi

# # 実行ファイルを削除
# rm -rf pipex