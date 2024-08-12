#include "minishell.h"



#define HEREDOCTMP ".heredoctmp"

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
        //malloc tmp_num
        tmp_num = ft_itoa(i);
        //malloc tmpfile
        tmpfile = ft_strjoin(HEREDOCTMP, tmp_num);
        //free tmp_num
        free(tmp_num);
        if (check_file_existence(tmpfile) == false)
            break;
        //free tmpfile
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
    while(1)
    {
        //malloc line
        line = readline(">");
        if (line == NULL)
            break;
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
        //malloc new_line
        new_line = ft_strjoin(line, "\n");
        //free line
        free(line);
        write(heredoc.tmpfile_fd, new_line, ft_strlen(new_line));
        //free new_line
        free(new_line);
    }
    close(heredoc.tmpfile_fd);
    heredoc.tmpfile_fd = open(heredoc.tmpfile, O_RDONLY);
    //free
    free(heredoc.tmpfile);

    return heredoc.tmpfile_fd;
    //if there is no error, opend file descriptor is returned 
}