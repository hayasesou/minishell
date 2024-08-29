#include "minishell.h"

#define SPECIFIED_DIR 1

static bool cd_valid_args(t_parser *parser, t_context *context)
{
    int args_count;
    args_count = 0;
    while(parser->cmd[args_count])
        args_count++;
    if(args_count > 2)
    {
        context->exit_status = NORMAL_ERROR;
        printf("minishell cd: too many arguments\n");
        return (false);
    }
    return (true);
}


void cd_builtin(t_parser *parser, t_context *context)
{
    char *new_dir;
    char *current_dir;
    char *old_dir;

    if(!cd_valid_args(parser, context))
        return ;

    if(parser->cmd[SPECIFIED_DIR] != NULL)
    {
        if (ft_strncmp(parser->cmd[SPECIFIED_DIR], "~", ft_strlen(parser->cmd[SPECIFIED_DIR])) == 0)
            new_dir = get_env_value("HOME", context->env_head);
        else if (ft_strncmp(parser->cmd[SPECIFIED_DIR], "-", ft_strlen(parser->cmd[SPECIFIED_DIR])) == 0)
            new_dir = get_env_value("OLDPWD", context->env_head);
        else
            new_dir = parser->cmd[SPECIFIED_DIR];

        if(new_dir == NULL)
        {
            context->exit_status = NORMAL_ERROR;
            printf("minishell cd: OLDPWD not set\n");
            return ;
        }
        if (ft_strncmp(parser->cmd[SPECIFIED_DIR], "-", ft_strlen(parser->cmd[SPECIFIED_DIR])) == 0)
            printf("%s\n", new_dir);
    }
    else
        new_dir = get_env_value("HOME", context->env_head);
    old_dir = get_env_value("PWD", context->env_head);
    set_env_value("OLDPWD", old_dir, context->env_head, context);
    free(old_dir); 
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

