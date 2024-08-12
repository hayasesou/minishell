#include "minishell.h"



void close_fd(int fd)
{
    if(close(fd) == -1)
    {
        fatal_error("close error");
    }
}


void dup2_fd(int old_fd, int new_fd)
{
    if(dup2(old_fd, new_fd) == -1)
    {
        fatal_error("dup2 error");
    }
    close_fd(old_fd);
}



void redirect(t_parser *parser, t_context *context, int *redirect_status)
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
            if (tmp_output_fd != -1)
                close_fd(tmp_output_fd);
            if(file->type == OUT_FILE)
            {
                tmp_output_fd = redirect_output(file, context,  redirect_status);
            }
            else if(file->type == APPEND)
                tmp_output_fd = append_output(file, context,  redirect_status);
        }
        else if (is_input(file))
        {
            if(tmp_input_fd != -1)
                close_fd(tmp_input_fd);
            if(file->type == IN_FILE)
            {
                tmp_input_fd = redirect_input(file, context,  redirect_status);
            }
            else if (file->type == HEREDOC)
            {
                tmp_input_fd = heredoc(file, context,  redirect_status);
            }
            else if (file->type == QUOTE_HEREDOC)
            {
                tmp_input_fd = quote_heredoc(file, context,  redirect_status);
            }
        }
       file = file->next;
    }

    if (tmp_output_fd != -1)
        dup2_fd(tmp_output_fd, STDOUT_FILENO);
    if (tmp_input_fd != -1)
        dup2_fd(tmp_input_fd, STDIN_FILENO);
}



__attribute__((destructor))
static void destructor() {
    system("leaks -q redirect");
}
int main(int ac, char **av, char **envp)
{
    t_parser parser;
    t_context context;
    int status;
    t_env *env_head = env_init(envp);
    // t_env *tmp = env_head->next;
    // while(tmp != env_head)
    // {
    //     printf("env_name: %s\n", tmp->env_name);
    //     printf("env_val: %s\n", tmp->env_val);
    //     tmp = tmp->next;
    // }
    context.env_head = env_head;

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

    // //redirect input cat < test1 < test2 < test3
    // f1.file_name = "test1";
    // f1.type = IN_FILE;
    // f1.next = &f2;
    // f2.file_name = "test2";
    // f2.type = IN_FILE;
    // f2.next = &f3;
    // f3.file_name = "test3";
    // f3.type = IN_FILE;
    // f3.next = NULL;

    // //mixture of redirect input and output cat < test1 > test2 < test3
    // //test3の中身がtest2にリダイレクトされる
    // f1.file_name = "test1";
    // f1.type = IN_FILE;
    // f1.next = &f2;
    // f2.file_name = "test2";
    // f2.type = OUT_FILE;
    // f2.next = &f3;
    // f3.file_name = "test3";
    // f3.type = IN_FILE;
    // f3.next = NULL;

    // //  cat >> test1 >> test2 < test3
    // f1.file_name = "test1";
    // f1.type = APPEND;
    // f1.next = &f2;
    // f2.file_name = "test2";
    // f2.type = APPEND;
    // f2.next = &f3;
    // f3.file_name = "test3";
    // f3.type = IN_FILE;
    // f3.next = NULL;

    // //cat << eof
    // f1.file_name = "eof";
    // f1.type = HEREDOC;
    // f1.next = NULL;
    // (void)f3;
    // (void)f2;

    // // cat << eof1 << eof2
    // f1.file_name = "eof1";
    // f1.type = HEREDOC;
    // f1.next = &f2;
    // f2.file_name = "eof2";
    // f2.type = HEREDOC;
    // f2.next = NULL;
    // (void)f3;


    // //cat << eof >test1
    // f1.file_name = "eof";
    // f1.type = HEREDOC;
    // f1.next = &f2;
    // f2.file_name = "test1";
    // f2.type = OUT_FILE;
    // f2.next = NULL;
    // (void)f3;

    // //cat > test1 << eof
    // f1.file_name = "test1";
    // f1.type = OUT_FILE;
    // f1.next = &f2;
    // f2.file_name = "eof";
    // f2.type = HEREDOC;
    // f2.next = NULL;
    // (void)f3;

    // //cat << eof1 << eof2 << eof3
    // f1.file_name = "eof1";
    // f1.type = HEREDOC;
    // f1.next = &f2;
    // f2.file_name = "eof2";
    // f2.type = HEREDOC;
    // f2.next = &f3;
    // f3.file_name = "eof3";
    // f3.type = HEREDOC;
    // f3.next = NULL;
    
    // //cat << eof1 > test2
    // //adapt to env_variable
    // f1.file_name = "eof1";
    // f1.type = HEREDOC;
    // f1.next = &f2;
    // f2.file_name = "test2";
    // f2.type = OUT_FILE;
    // f2.next = NULL;
    // (void)f3;


    // // //cat << eof1
    // f1.file_name = "eof1";
    // f1.type = HEREDOC;
    // f1.next = NULL;
    // (void)f3;
    // (void)f2;

    //heredoc quote test
    // cat << " "
    f1.file_name = " ";
    f1.type = QUOTE_HEREDOC;
    f1.next = NULL;
    (void)f2;
    (void)f3;

    parser.file = &f1;
    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        fatal_error("fork error");
    }
    if(pid == 0)
    {
        redirect(&parser, &context, &status);
        char *cmd[] = {"cat", NULL};
        execve("/usr/bin/cat", cmd, NULL);
        printf("execve error");
    }
    waitpid(pid, &status, 0);
    delete_tmpfile();
    
    printf("success\n");

    return 0;
}
