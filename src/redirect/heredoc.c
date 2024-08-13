#include "minishell.h"

int heredoc(t_file *file, t_context *context, int *redirect_status)
{
    t_heredoc heredoc;
    (void)redirect_status;

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
        //user input the deliminater
        if (ft_strncmp(line, heredoc.deliminater, ft_strlen(line)) == 0 && ft_strlen(line) == ft_strlen(heredoc.deliminater))
        {
            free(line);
            break;
        }
        // //malloc new_line
        // new_line = ft_strjoin(line, "\n");
        // //free line
        // free(line);
        new_line = heredoc_expantion(line, context);

        write(heredoc.tmpfile_fd, new_line, ft_strlen(new_line));
        write(heredoc.tmpfile_fd, "\n", 1);

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


int quote_heredoc(t_file *file, t_context *context, int *redirect_status)
{
    t_heredoc heredoc;
    (void)redirect_status;

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