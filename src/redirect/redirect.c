#include "minishell.h"


int redirect_output(t_file *file, int *status)
{
    (void)status;
    int fd;
    fd = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
    {
        fatal_error("open error\n");
    }
    return fd;
}

int append_output(t_file *file, int *status)
{
    (void)status;
    int fd;
    fd = open(file->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd == -1)
    {
        fatal_error("open error\n");
    }
    return fd;
}

bool is_output(t_file *file)
{
    return (file->type == OUT_FILE || file->type == APPEND);
}


int redirect_input(t_file *file, int *status)
{
    (void)status;
    int fd = open(file->file_name, O_RDONLY);
    if(fd == -1)
    {
        fatal_error("open error\n");
    }
    return fd;
}




bool is_input(t_file *file)
{
    return (file->type == IN_FILE || file->type == HEREDOC || file->type == QUOTE_HEREDOC);
}


void redirect(t_parser *parser, t_context *context, int *status)
{
    int tmp_input_fd;
    int tmp_output_fd;
    t_file *file;

    file = parser->file;
    tmp_input_fd = -1;
    tmp_output_fd = -1;

    while(file != NULL)
    {
        if (is_output(file))
        {
            if(file->type == OUT_FILE)
            {
                tmp_output_fd = redirect_output(file, status);
                if (file->next != NULL)
                        close(tmp_output_fd);
            }
            else if(file->type == APPEND)
                tmp_output_fd = append_output(file, status);
        }
        else if (is_input(file))
        {
            if(file->type == IN_FILE)
            {
                tmp_input_fd = redirect_input(file, status);
                if(file->next != NULL)
                    close(tmp_input_fd);
            }
        }
       file = file->next;
    }
    dup2(tmp_output_fd, STDOUT_FILENO);
    dup2(tmp_input_fd, STDIN_FILENO);
}


int main(void)
{
    t_parser parser;
    t_context context;
    int status;

    t_file f1, f2, f3;
    //redirect output    ls > test1 > test2 > test3
    // f1.file_name = "test1";
    // f1.type = OUT_FILE;
    // f1.next = &f2;
    // f2.file_name = "test2";
    // f2.type = OUT_FILE;
    // f2.next = &f3;
    // f3.file_name = "test3";
    // f3.type = OUT_FILE;
    // f3.next = NULL;


    // //redirect output append   ls >> test1 >> test2 >> test3
    // f1.file_name = "test1";
    // f1.type = APPEND;
    // f1.next = &f2;
    // f2.file_name = "test2";
    // f2.type = APPEND;
    // f2.next = &f3;
    // f3.file_name = "test3";
    // f3.type = APPEND;
    // f3.next = NULL;

    // //mixture of redirect outtput and append ls > test1 >> test2 > test3
    // f1.file_name = "test1";
    // f1.type = OUT_FILE;
    // f1.next = &f2;
    // f2.file_name = "test2";
    // f2.type = APPEND;
    // f2.next = &f3;
    // f3.file_name = "test3";
    // f3.type = OUT_FILE;
    // f3.next = NULL;

    //redirect input cat < test1 < test2 < test3
    f1.file_name = "test1";
    f1.type = IN_FILE;
    f1.next = &f2;
    f2.file_name = "test2";
    f2.type = IN_FILE;
    f2.next = &f3;
    f3.file_name = "test3";
    f3.type = IN_FILE;
    f3.next = NULL;




    parser.file = &f1;
    redirect(&parser, &context, &status);

    char *cmd[] = {"cat", NULL};
    execve("/usr/bin/cat", cmd, NULL);
    printf("execve error");   

    return 0;
}
