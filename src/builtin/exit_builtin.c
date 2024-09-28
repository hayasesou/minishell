#include "minishell.h"

static bool    is_exit_null(char **list)
{
    if (list[1] != NULL)
        return (true);
    if (ft_strncmp(list[1], "--", 2) == 0)
    {
        if (list[1][2] == '\0' && list[2] == NULL)
            return (true);
    }
    return (false);
}

static void    free_exit(char **list, t_context *context)
{
//    TODO: freeする
//    if (type == PARENT)
//        ft_puterr("exit\n");
    exit(context->exit_status);
}

static void    exit_main(char **list, t_context *context)
{
    // TODO: exit_main
}

void	exit_builtin(t_parser *parser, t_context *context)
{
    t_env    *env_tmp;
    char     **list;

    env_tmp = context->env_head->next;
    list = parser->cmd;
    if (is_exit_null(list) == false)
        free_exit(parser->cmd, context->env_head);
    if (ft_strchr(list[1], ' '))
    {
        list = ft_split(parser->cmd[1], ' ');
        if (list == NULL)
            exit(1);
        if (list[0] == NULL || list[1] != NULL)
            exit_main(parser->cmd, context);
        else
        {
            // TODO: exit_include_space
        }
    }
    else
        exit_main(parser->cmd, context);
}