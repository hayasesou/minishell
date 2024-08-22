#include "minishell.h"


void process_heredoc(t_parser *parser_head, t_context *context, int *heredoc_status)
{
    t_parser *tmp_parser;
    t_file *file;

    tmp_parser = parser_head;
    while(tmp_parser != NULL)
    {
       file = tmp_parser->file;
       while(file != NULL)
       {
           if (file->type == HEREDOC)
           {
                file->heredoc_fd = heredoc(file, context, heredoc_status);
           }
           else if(file->type == QUOTE_HEREDOC)
           {
                file->heredoc_fd = quote_heredoc(file, context, heredoc_status);
           }
           file = file->next;
       }
        tmp_parser = tmp_parser->next;
    }
}


void setup_heredoc_fd(t_parser *parser)
{
    t_file *file = parser->file;
    while(file != NULL)
    {
        if (file->type == HEREDOC || file->type == QUOTE_HEREDOC)
        {
            dup2(file->heredoc_fd, STDIN_FILENO);
            close(file->heredoc_fd);
        }
        file = file->next;
    }
}


void close_heredoc_fds(t_parser *parser)
{
    t_file *file = parser->file;
    while(file != NULL)
    {
        if (file->type == HEREDOC || file->type == QUOTE_HEREDOC)
        {
            close(file->heredoc_fd);
        }
        file = file->next;
    }
}

