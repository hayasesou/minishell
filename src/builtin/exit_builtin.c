#include "minishell.h"

void ft_puterr(char *str)
{
    write(2, str, ft_strlen(str));
}

bool is_overflow(const char *str, long *result)
{
    int i;
    int sign;
    unsigned long num;
    unsigned long cutoff;
    int cutlim;

    i = 0;
    sign = 1;
    num = 0;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    if (sign == -1)
        cutoff = -(unsigned long)LONG_MIN;
    else
        cutoff = LONG_MAX;
    cutlim = cutoff % 10;
    cutoff /= 10;
    while (str[i])
    {
        int c = str[i++] - '0';

        if (num > cutoff || (num == cutoff && c > cutlim))
            return true;

        num = num * 10 + c;
    }
    if (sign == -1)
        *result = -(long)num;
    else
        *result = (long)num;

    return false;
}

bool is_valid_number(const char *str)
{
    int i = 0;

    if (str[i] == '\0')
        return (false);
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (str[i] == '\0') // 符号のみの場合
        return (false);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (false);
        i++;
    }
    return (true);
}


static void	print_numeric_error(char *status, bool is_parent)
{
    if (is_parent)
        ft_puterr("minishell: exit: ");
    ft_puterr("minishell: exit: ");
    ft_puterr(status);
    ft_puterr(": numeric argument required\n");
}

static void	print_too_many_args(bool is_parent)
{
    if (is_parent)
        ft_puterr("exit\n");
    ft_puterr("minishell: exit: too many arguments\n");
}

static void	cleanup_and_exit(t_context *context, int exit_code)
{
    free_all(context);
    exit(exit_code);
}

void    exit_builtin(t_parser *parser, t_context *context)
{
    char    **cmd;
    long    exit_code;
    int     final_exit_code;
    bool    is_parent;
    pid_t   pid;

    pid = getpid();
    if (pid == 0)
        is_parent = false;
    else
        is_parent = true;
    cmd = parser->cmd;
    exit_code = 0;
    if (cmd[1] == NULL)
    {
        if (is_parent)
            ft_puterr("exit\n");
        cleanup_and_exit(context, context->exit_status);
    }

    if (!is_valid_number(cmd[1]) || is_overflow(cmd[1], &exit_code))
    {
        print_numeric_error(cmd[1], is_parent);
        cleanup_and_exit(context, 255);
    }
    
    if (cmd[2] != NULL)
    {
        print_too_many_args(is_parent);
        context->exit_status = 1;
        return; // シェルを終了させないらしい
    }
    final_exit_code = (int)(exit_code % 256);
    if (final_exit_code < 0)
        final_exit_code += 256;

    if (is_parent)
        ft_puterr("exit\n");

    cleanup_and_exit(context, final_exit_code);
}
