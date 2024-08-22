#include "minishell.h"


//confirm the existence of the file in the current directory
static bool check_file_existence(char *file_name)
{
    if (access(file_name, F_OK) == -1)
        return  false;
    return true;
}

void create_tmpfile(t_heredoc *heredoc, t_context *context, int *heredoc_status)
{
    int fd;
    char *tmpfile;
    char *tmp_num;
    int i;

    i = 0;
    while(1)
    {
        //malloc tmp_num
        tmp_num = ft_itoa(i);
        if(tmp_num == NULL)
        {
            context->exit_status = 1;
            *heredoc_status = 1;
            fatal_error("malloc error");
        }
        //malloc tmpfile
        tmpfile = ft_strjoin(HEREDOCTMP, tmp_num);
        //free tmp_num
        free(tmp_num);
        if(tmpfile == NULL)
        {
            context->exit_status = 1;
            *heredoc_status = 1;
            fatal_error("malloc error");
        }
        if (check_file_existence(tmpfile) == false)
            break;
        //free tmpfile
        free(tmpfile);
        i++;
    }
    fd = open(tmpfile, O_WRONLY | O_CREAT | O_APPEND , 0644);
    if(fd == -1)
    {
        context->exit_status = 1;
        *heredoc_status = 1;
        error_message("tmpfile");
        free(tmpfile);
    }
    heredoc->tmpfile = tmpfile;
    heredoc->tmpfile_fd = fd;
    //If there is no error, the allocated memory area is assigned to tmpfile
    //if there is no error, opened file descriptor is assigned to tmpfile_fd
    //if there is no error, tmp file is created
}

void delete_tmpfile(void)
{
    char *tmp_num;
    char *tmpfile;
    int i;

    i = 0;
    //malloc tmp_num
    tmp_num = ft_itoa(i);
    //maloc tmpfile
    tmpfile = ft_strjoin(HEREDOCTMP, tmp_num);
    //free tmp_num
    free(tmp_num);
    while(access(tmpfile, F_OK) != -1)
    {
        //delete tmpfile
        unlink(tmpfile);
        //free tmpfile
        free(tmpfile);
        i++;
        tmp_num = ft_itoa(i);
        tmpfile = ft_strjoin(HEREDOCTMP, tmp_num);
        free(tmp_num);
        if (tmpfile == NULL)
            fatal_error("malloc error");
    }
    //free tmpfile
    free(tmpfile);
}