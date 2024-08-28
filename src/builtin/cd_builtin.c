#include "minishell.h"

#define SPECIFIED_DIR 1


void cd_builtin(t_parser *parser, t_context *context)
{
    char *new_dir;
    char *current_dir;

    set_env_value("OLDPWD", get_env_value("PWD", context->env_head), context->env_head, context);
    if( parser->cmd[SPECIFIED_DIR] != NULL)
    {
        if (ft_strncmp(parser->cmd[SPECIFIED_DIR], "~", ft_strlen(parser->cmd[SPECIFIED_DIR])) == 0)
            new_dir = get_env_value("HOME", context->env_head);
        else if (ft_strncmp(parser->cmd[SPECIFIED_DIR], "-", ft_strlen(parser->cmd[SPECIFIED_DIR])) == 0)
            new_dir = get_env_value("OLDPWD", context->env_head);
        else
            new_dir = parser->cmd[SPECIFIED_DIR];
    }
    else
        new_dir = get_env_value("HOME", context->env_head);
    if (chdir(new_dir) == -1)
    {
        free(new_dir);
        new_dir = NULL;
        context->exit_status = NORMAL_ERROR;
        perror("minishell cd");
        return ;
        // exit(NORMAL_ERROR);
    }
    free(new_dir);
    current_dir = getcwd(NULL, 0);
    set_env_value("PWD", current_dir, context->env_head, context);
    free(current_dir);
}

