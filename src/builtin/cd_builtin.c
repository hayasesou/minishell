#include "minishell.h"

#define SPECIFIED_DIR 1


void cd_builtin(t_parser *parser, t_context *context)
{
    char *new_dir;
    char *current_dir;

    set_env_value("OLDPWD", get_env_value("PWD", context->env_head), context->env_head, context);
    if( parser->cmd[SPECIFIED_DIR] != NULL)
        new_dir = parser->cmd[SPECIFIED_DIR];
    else
        new_dir = get_env_value("HOME", context->env_head);

    if (chdir(new_dir) == -1)
    {
        free(new_dir);
        context->exit_status = NORMAL_ERROR;
        perror("minishell cd");
        exit(NORMAL_ERROR);
    }
    free(new_dir);
    current_dir = getcwd(NULL, 0);
    set_env_value("PWD", current_dir, context->env_head, context);
    free(current_dir);

    printf("get_cwd: %s\n", getcwd(NULL, 0));
    printf("pwd: %s\n", get_env_value("PWD", context->env_head));
    printf("oldpwd: %s\n", get_env_value("OLDPWD", context->env_head));

    context->exit_status = NORMAL_EXIT;
    exit(NORMAL_EXIT);
}

