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

static void have_n_option(t_parser *tmp_parser)
{
    (void)tmp_parser;
    ft_printf("have_n_option\n");
}

static void no_n_option(t_parser *tmp_parser)
{
    (void)tmp_parser;
    ft_printf("no_n_option\n");
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
            have_n_option(tmp_parser);
            tmp_parser = tmp_parser->next;
        }
    }
    else
    {
        while (tmp_parser)
        {
            no_n_option(tmp_parser);
            tmp_parser = tmp_parser->next;
        }
    }
}