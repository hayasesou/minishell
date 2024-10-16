#include "minishell.h"

static void	print_numeric_error(t_context *context, char *str)
{
    ft_puterr("minishell: exit: ");
    ft_puterr(str);
    ft_puterr(": numeric argument required\n");
    free_env(context->env_head);
    context->exit_status = 255;
    exit(255);
}

static void	print_too_many_args(t_context *context)
{
    ft_puterr("minishell: exit: too many arguments\n");
    context->exit_status = 1;
}

void    exit_space(char **cmd, char **new_cmd, t_context *context)
{
    if (!is_valid_number(new_cmd[0]) || is_overflow(new_cmd[0]))
    {
        free_cmd(new_cmd);
        print_numeric_error(context, cmd[1]);
    }
    if (new_cmd[1] != NULL)
        print_too_many_args(context);
    else
    {
        free_cmd(new_cmd);
        exit (ft_atoi(cmd[1]) % 256);
    }
}

void    exit_main(char **cmd, t_context *context)
{

    if (!is_valid_number(cmd[1]) || is_overflow(cmd[1]))
    {
        print_numeric_error(context, cmd[1]);
        cleanup_and_exit(context, 255);
    }
    if (cmd[2] != NULL)
        print_too_many_args(context); // ここexitしないでOK？
    else
        exit (ft_atoi(cmd[1]) % 256);
}

void    exit_builtin(t_parser *parser, t_context *context, bool is_parent)
{
    char    **cmd;
    char    **new_cmd;

    cmd = parser->cmd;
    if (is_parent)
        ft_puterr("exit\n");
    if (cmd[1] == NULL || !ft_strncmp("--", cmd[1], 2))
        cleanup_and_exit(context, context->exit_status);
    if (ft_strchr(cmd[1], ' '))
    {
        new_cmd = ft_split(cmd[1], ' ');
        if (new_cmd == NULL)
            exit(1);
        if (new_cmd[0] == NULL || new_cmd[1] != NULL)
            exit_main(cmd, context);
        else
            exit_space(cmd, new_cmd, context);
    }
    else
        exit_main(cmd, context);
}
