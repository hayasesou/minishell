# 現在のディレクトリ内の .c ファイルをすべて取得
redirect_files=$(ls *.c)

# 必要なインクルードディレクトリを指定
Include="-I../../include -I../../libft"
LFALGS="-L../../libft -lft"
H_FLAGS="-lreadline"

# コンパイル
cc $redirect_files ../error.c $Include $LFALGS -Wall -o redirect $H_FLAGS

# コンパイルが成功した場合のみ実行
if [ $? -eq 0 ]; then
    ./redirect
else
    echo "Compilation failed."
    exit 1
fi

# 実行ファイルを削除
# rm -rf redirect