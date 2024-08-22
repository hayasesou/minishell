#include "minishell.h"

int heredoc(t_file *file, t_context *context, int *heredoc_status)
{
    t_heredoc heredoc;
    char *line;
    char *new_line;

    heredoc.deliminater = file->file_name;
    create_tmpfile(&heredoc, context, heredoc_status);
    while(1)
    {
        line = readline(">");
        if (line == NULL)
            break;
        if (ft_strncmp(line, heredoc.deliminater, ft_strlen(line)) == 0 && ft_strlen(line) == ft_strlen(heredoc.deliminater))
        {
            free(line);
            break;
        }
        new_line = heredoc_expantion(line, context, heredoc_status);
        if(new_line == NULL)
        {
            context->exit_status = 1;
            break;
        }
        write(heredoc.tmpfile_fd, new_line, ft_strlen(new_line));
        write(heredoc.tmpfile_fd, "\n", 1);
        free(new_line);
    }
    close(heredoc.tmpfile_fd);
    heredoc.tmpfile_fd = open(heredoc.tmpfile, O_RDONLY);
    free(heredoc.tmpfile);
    return heredoc.tmpfile_fd;
}


int quote_heredoc(t_file *file, t_context *context, int *heredoc_status)
{
    t_heredoc heredoc;
    char *line;
    char *new_line;

    heredoc.deliminater = file->file_name;
    create_tmpfile(&heredoc, context, heredoc_status);
    while(1)
    {
        line = readline(">");
        if (line == NULL)
            break;
        if (ft_strncmp(line, heredoc.deliminater, ft_strlen(line)) == 0 && ft_strlen(line) == ft_strlen(heredoc.deliminater))
        {
            free(line);
            break;
        }
        new_line = ft_strjoin(line, "\n");
        free(line);
        if(new_line == NULL)
        {
            context->exit_status = 1;
            *heredoc_status = 1;
            break;
        }
        write(heredoc.tmpfile_fd, new_line, ft_strlen(new_line));
        free(new_line);
    }
    close(heredoc.tmpfile_fd);
    heredoc.tmpfile_fd = open(heredoc.tmpfile, O_RDONLY);
    free(heredoc.tmpfile);
    return heredoc.tmpfile_fd;
}