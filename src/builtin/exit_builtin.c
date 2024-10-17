#include "minishell.h"

static void	print_numeric_error(t_context *context, char *str)
{
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": numeric argument required\n", 2);
    free_env(context->env_head);
    context->exit_status = NUMERIC_ERROR;
    exit(NUMERIC_ERROR);
}

static void	print_too_many_args(t_context *context)
{
    ft_putstr_fd("minishell: exit: too many arguments\n", 2);
    context->exit_status = NORMAL_ERROR;
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
        cleanup_and_exit(context, NUMERIC_ERROR);
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
        ft_putstr_fd("exit\n", 1);
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
