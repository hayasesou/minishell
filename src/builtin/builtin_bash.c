#include "minishell.h"

#define PROGRAM_NAME "./minishell"

static void check_file_and_execute(t_parser *parser, t_context *context, char *cmd_path)
{

    char **env_list;

    if (access(cmd_path, F_OK) == 0)
    {
        if(access(cmd_path, X_OK) == 0)
        {
            if(ft_strncmp(parser->cmd[0], PROGRAM_NAME, ft_strlen(PROGRAM_NAME)) == 0)
                set_env_value("SHLVL", ft_itoa(ft_atoi(get_env_value("SHLVL", context->env_head)) + 1), context->env_head, context);

            env_list = make_env_list(context->env_head, context);
            execve(cmd_path, parser->cmd, env_list);
            free(cmd_path);
            free_env_list(env_list);
            ft_printf("execve error\n");
            free_all_env_node(context->env_head);
            context->exit_status = NORMAL_ERROR;
            exit(NORMAL_ERROR);
        }
        else
        {
            ft_printf("minishell : %s: Permission denied\n", parser->cmd[0]);
            free_all_env_node(context->env_head);
            context->exit_status = PERMISSION_DENIED;
            exit(PERMISSION_DENIED);
        }
    }
    return;  
}


// "path" + "/" + "cmd"
//e.g.) "/usr/bin" + "/" + "ls"
static char *make_cmd_path(char *path, int start, int i, t_parser *parser)
{
    char *stash_dir1;
    char *stash_dir2;
    char *cmd_path;

    stash_dir1 = ft_substr(path, start, i - start);
    if(stash_dir1 == NULL)
        return (NULL);
    stash_dir2 = ft_strjoin(stash_dir1, "/");
    free(stash_dir1);
    if(stash_dir2 == NULL)
        return (NULL);
    cmd_path = ft_strjoin(stash_dir2, parser->cmd[0]);
    free(stash_dir2);
    if(cmd_path == NULL)
        return (NULL);
    return cmd_path;
}

//imginable input of t_parsaer->cmd[0]: ls or usr/bin/ls or usr/bin  or ./a.out
void bash_builtin(t_parser *parser, t_context *context)
{
    char *path;
    int i;
    int start;
    char* cmd_path;
    struct stat st; 

    path = get_env_value("PATH", context->env_head); 
    if(path == NULL)
    {
        context->exit_status = NORMAL_ERROR;
        ft_printf("PATH not found\n");
        exit(NORMAL_ERROR);
    }
    start = 0;
    i = 0;
    
    // "binary file path" or "directory path"
    //e.g.) "/usr/bin/ls" "/usr/bin" "./a.out"
    if(ft_strchr(parser->cmd[0], '/') != NULL)
    {
        if(stat(parser->cmd[0], &st) == 0)
        {
            if(S_ISDIR(st.st_mode))
            {
                ft_printf("minishell : %s: Is a directory\n", parser->cmd[0]);
                context->exit_status = IS_DIR;
                exit(IS_DIR);
            }
            check_file_and_execute(parser, context, parser->cmd[0]);
        }
        return ;
    }
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
    free(path);
}