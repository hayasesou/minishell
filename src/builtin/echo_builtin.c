#include "../../include/minishell.h"

static bool is_n_option(char *op)
{
    if (*op == '\0')
        return (false);
    if (ft_strncmp("-n", op, 2) == 0)
    {
        if (ft_strlen(op) <= 2)
            return (true);
        else
            op += 2;
    }
    while (*op && *op == 'n')
        op++;
    if (*op)
        return (false);
    return (true);
}

static int count_command(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i] != NULL)
        i++;
    return (i);
}

static void have_n_option(char **cmd)
{
    int i;
    int cmd_size;

    i = 1;
    cmd_size = count_command(cmd);
    while (i < cmd_size)
    {
        if (!is_n_option(cmd[i]))
        {
            ft_printf("%s", cmd[i]);
            if (i < cmd_size - 1)
                ft_printf(" ");
        }
        i++;
    }
}

static void no_n_option(char **cmd)
{
    int i;
    int cmd_size;

    i = 1;
    cmd_size = count_command(cmd);
    while (i < cmd_size)
    {
        ft_printf("%s", cmd[i]);
        if (i < cmd_size - 1)
            ft_printf(" ");
        i++;
    }
    ft_printf("\n");
}

void    echo_builtin(t_parser *parser, t_context *context)
{
    t_parser *tmp_parser;

    tmp_parser = parser;
    (void)context;
    if (tmp_parser->cmd[1] && is_n_option(tmp_parser->cmd[1]))
    {
        while (tmp_parser)
        {
            have_n_option(tmp_parser->cmd);
            tmp_parser = tmp_parser->next;
        }
        context->exit_status = 0;
    }
    else
    {
        while (tmp_parser)
        {
            no_n_option(tmp_parser->cmd);
            tmp_parser = tmp_parser->next;
        }
        context->exit_status = 0;
    }
}