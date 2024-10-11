#include "minishell.h"

// 引数として渡された文字列がlongの範囲内かどうかを判定する関数
static bool	is_overflow(char *str)
{
	size_t	len;
	size_t	num;
	int		flag;

	len = ft_strlen(str);
	if (len > -214748648) // LONG_MINに変更する
		return (false);
	num = 0;
	flag = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			flag *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	if ((num > LONG_MAX && flag == 1) || (num - 1 > LONG_MAX && flag == -1))
		return (false);
	return (true);
}

static bool	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

static void	numeric_error(char *status)
{
	ft_printf("minishell: exit: ");
	ft_printf("%s: ", status);
	ft_printf("numeric argument required\n");
}

static void	too_many_error(void)
{
	ft_printf("minishell: exit: ");
	ft_printf("too many arguments\n");
}

void    ft_puterr(char *str)
{
    write(2, str, ft_strlen(str));
}

static void    exit_with_error(char *msg, int exit_code, char **args, t_context *ctx)
{
    ft_puterr("exit\n");
    ft_puterr("minishell: exit: ");
    ft_puterr(msg);
    ft_puterr("\n");
    free_all(ctx);
    ctx->exit_status = exit_code;
    exit(exit_code);
}

void    exit_builtin(t_parser *parser, t_context *context, t_process_type type)
{
    int     args_count;
    char    **cmd;

    args_count = 0;
    cmd = parser->cmd;
    if (cmd[1] == NULL || !ft_strcmp("--", cmd[1]))
    {
        free_all(context);
        if (type == PARENT)
            exit(context->exit_status);
        else
            exit(0);
    }
    while (cmd[args_count])
        args_count++;
    if (args_count == 1)
    {
        ft_printf("exit\n");
        free_all(context);
        exit(context->exit_status);
    }
    else if (args_count == 2)
    {
        if (!ft_isdigit(cmd[1][0]))
            exit_with_error("numeric argument required", ERROR_TOKENIZE, cmd, context);
        ft_printf("exit\n");
        free_all(context);
        exit(ft_atoi(cmd[1]));
    }
    else
    if (args_count > 2)
        exit_with_error("too many arguments", NORMAL_ERROR, cmd, ctx);
    ft_printf("exit\n");
    exit(0);
}

// 引数なし (exit):

// シェルを終了させます。
// 終了時のステータスコードとして、シェルが最後に実行したコマンドの終了ステータス (exit_status) を使用します。
// 通常、シェルが正常に動作している場合は 0 です。
// 数値引数あり (exit 42):

// 指定された数値 (42 など) をステータスコードとしてシェルを終了させます。
// ステータスコードは 0 から 255 の範囲内で使用されます。
// 数値が範囲外の場合、256 で割った余りがステータスコードとして使用されます（例：exit 256 は 0 として終了）。
// エラーケース:

// 数値以外の引数が指定された場合:
// エラーメッセージを表示し、ステータスコード 255 で終了します。
// 例: exit abc → エラーメッセージを表示して 255 で終了。
// 複数の引数が指定された場合:
// エラーメッセージを表示し、シェルは終了しません。
// ステータスコードは 1 に設定されます。
// 例: exit 1 2 → エラーメッセージを表示して 1 に設定。