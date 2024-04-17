#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


typedef struct s_pipex
{
    int input_fd;
    int output_fd;
    int pipefd[2];
} t_pipex;


int bufsize = 100;


int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;
    pid_t pid1;

    (void)argc;
    (void)argv;
    (void)envp;
    char *buf;
    int count ;

    buf = (char*)malloc(sizeof(char) * bufsize);

    if (pipe(pipex.pipefd) == -1)
        exit(1);
    
    char *file_path = "/usr/bin/ls";
    char *args[] = {"ls", "-l", NULL};

    pid1 = fork();
    if(pid1 == 0)
    {
        printf("child process\n");
        dup2(pipex.pipefd[1], STDOUT_FILENO);
        close(pipex.pipefd[1]);
        close(pipex.pipefd[0]);
        execve(file_path, args, envp);
    
        printf("execv failed\n");
    }
    else
    {
        waitpid(pid1, NULL, 0);
        while(1)
        {
            // write(1, "parent process\n", 16);
            count = read(pipex.pipefd[0], buf, bufsize);
            if (count < bufsize)
            {
                write(STDOUT_FILENO, buf, count);
                break;
            }

            write(STDOUT_FILENO, buf, bufsize);
        }
        printf("parent process\n");
    }

    return 0;
}