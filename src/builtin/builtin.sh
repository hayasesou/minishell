#現在のディレクトリ内の.c ファイルをすべて取得
builtin_files=$(ls *.c)

# 必要なインクルードディレクトリを指定
Include="-I../../include -I../../libft"
LFALGS="-L../../libft -lft"
H_FLAGS="-lreadline"
C_FLAGS="-g -fsanitize=address"

# コンパイル
cc $C_FLAGS $builtin_files ../error.c ../env.c $Include $LFALGS -Wall -Werror -Wextra -o builtin $H_FLAGS