#include "minishell.h"

static void check_file_and_execute(t_parser *parser, t_context *context, char *cmd_path)
{

    char **env_list;
    if (access(cmd_path, F_OK) == 0)
    {
        if(access(cmd_path, X_OK) == 0)
        {
            env_list = make_env_list(context->env_head, context);
            execve(cmd_path, parser->cmd, env_list);
            free(cmd_path);
            free_env_list(env_list);
            printf("execve error\n");
            context->exit_status = NORMAL_ERROR;
            exit(NORMAL_ERROR);
        }
        else
        {
            context->exit_status = PERMISSION_DENIED;
            printf("Permission denied\n");
            exit(PERMISSION_DENIED);
        }
    }
    
}



//e.g.) usr/bin + / + ls
static char *make_cmd_path(char *path, int start, int i, t_parser *parser)
{
    char *stash_dir1;
    char *stash_dir2;
    char *cmd_path;

    stash_dir1 = ft_substr(path, start, i - start);
    stash_dir2 = ft_strjoin(stash_dir1, "/");
    free(stash_dir1);
    cmd_path = ft_strjoin(stash_dir2, parser->cmd[0]);
    free(stash_dir2);
    
    return cmd_path;
}


void bash_builtin(t_parser *parser, t_context *context)
{
    char *path;
    int i;
    int start;
    char* cmd_path; 

    path = getenv("PATH"); 
    if(path == NULL)
    {
        context->exit_status = NORMAL_ERROR;
        printf("PATH not found\n");
        exit(NORMAL_ERROR);
    }
    start = 0;
    i = 0;
    while(path[i] != '\0')
    {
        if(path[i] == ':')
        {
            cmd_path = make_cmd_path(path, start, i, parser); 
            check_file_and_execute(parser, context, cmd_path);
            free(cmd_path);
            start = i + 1;
        }
        i++;
    }
}