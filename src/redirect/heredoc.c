#include "minishell.h"


typedef struct s_heredoc
{
    char *deliminater;
    char *tmpfile;
    int tmpfile_fd;
}   t_heredoc;


//confirm the existence of the file in the current directory
bool check_file_existence(char *file_name)
{
    if (access(file_name, F_OK) == -1)
        return  false;
    return true;
}

void create_tmpfile(t_heredoc *heredoc)
{
    int fd;
    char *tmpfile;
    char *tmp_num;
    int i;

    i = 0;
    while(1)
    {
        //malloc
        tmp_num = ft_itoa(i);
        //malloc
        tmpfile = ft_strjoin("heredoctmp", tmp_num);
        //free 
        free(tmp_num);
        if (check_file_existence(tmpfile) == false)
            break;
        //free
        free(tmpfile);
        i++;
    }
    fd = open(tmpfile, O_WRONLY | O_CREAT | O_APPEND , 0644);
    if(fd == -1)
    {
        error_message("tmpfile");
        free(tmpfile);
    }
    heredoc->tmpfile = tmpfile;
    heredoc->tmpfile_fd = fd;
}


int heredoc(t_file *file, t_context *context, int *redirect_status)
{
    t_heredoc heredoc;

    heredoc.deliminater = file->file_name;
    create_tmpfile(&heredoc);
    if(heredoc.tmpfile_fd == -1)
    {
        context->exit_status = 1;
        free(heredoc.tmpfile);
        close(heredoc.tmpfile_fd);
        return 0;
    }
    //heredoc = {
    //     .deliminater = file->file_name;
    //     .tmpfile = tmpfile;
    //     .tmpfile_fd = fd;
    // }

    // read from stdin and write to tmpfile
    char *line;
    char *new_line;
    // printf("%d",heredoc.tmpfile_fd);
    while(1)
    {
        line = readline(">");
        if (line == NULL)
            break;
        // blank line
        if(ft_strlen(line) == 0)
        {
            free(line);
            continue;
        }
        //user input the deliminater
        if (ft_strncmp(line, heredoc.deliminater, ft_strlen(line)) == 0 && ft_strlen(line) == ft_strlen(heredoc.deliminater))
        {
            free(line);
            break;
        }
        new_line = ft_strjoin(line, "\n");
        free(line);
        write(heredoc.tmpfile_fd, new_line, ft_strlen(new_line));
        free(new_line);
    }
    //tmpfilefd is WRITE ONLY so we need to close it and reopen it as READ ONLY
    close(heredoc.tmpfile_fd);
    heredoc.tmpfile_fd = open(heredoc.tmpfile, O_RDONLY);
    //free
    // free(heredoc.tmpfile);
    // printf("%d",heredoc.tmpfile_fd);
    return heredoc.tmpfile_fd;
}