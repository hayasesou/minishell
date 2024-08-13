#include "minishell.h"

//if you use env which is not defined in redirect output, bash will display "ambiguous redirect"
//e.g)
//echo aaaa > $undefined_env
//bash: $undeifned_env: ambiguous redirect
//before redireting, our bash  will do expantion and if it is not defined in env, it will make "\0" string 
int redirect_output(t_file *file, t_context *context,  int *status)
{
    (void)status;
    int fd;

    if (file->file_name[0] == '\0')
    {
        unexisted_env_error(file->file_name);
        context->exit_status = 1;
        return 0;
    }
    fd = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
    {
        context->exit_status = 1;
        error_message(file->file_name);
        return 0;
    }
    context->exit_status = 0;
    return fd;
}


//if you use env which is not defined in redirect append, bash will display "ambiguous redirect"
//e.g)
//echo aaaa >> $undefined_env
//bash: $undeifned_env: ambiguous redirect
//before redireting, our bash  will do expantion and if it is not defined in env, it will make "\0" string 
int append_output(t_file *file, t_context *context,int *status)
{
    (void)status;
    int fd;

    if (file->file_name[0] == '\0')
    {
        context->exit_status = 1;
        unexisted_env_error(file->file_name);
        return 0;
    }
    fd = open(file->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd == -1)
    {
        context->exit_status = 1;
        error_message(file->file_name);
        return 0;
    }
    context->exit_status = 0;
    return fd;
}

bool is_output(t_file *file)
{
    return (file->type == OUT_FILE || file->type == APPEND);
}