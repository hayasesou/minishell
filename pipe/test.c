#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define WRITE 1
#define READ 0

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
    // pid_t pid2;
    (void)argc;
    (void)argv;
    (void)envp;


    if (pipe(pipex.pipefd) == -1)
        exit(1);
    
    char *file_path1 = "/usr/bin/ls";
    char *args1[] = {"ls", "-l", NULL};
    char *file_path2 = "/usr/bin/wc";
    char *args2[] = {"wc", "-l", NULL};

    pid1 = fork();
    if(pid1 == -1)
    {
      printf("fork error\n"); 
      exit(1); 
    }
    //child process
    if(pid1 == 0)
    {
        printf("child process\n");
        dup2(pipex.pipefd[WRITE], STDOUT_FILENO);
        close(pipex.pipefd[READ]);
        execve(file_path1, args1, envp);
        printf("execv failed\n");
    }
    else
    {
      //parent process
        waitpid(pid1, NULL, 0);
        printf("parent process\n");
        close(pipex.pipefd[WRITE]);
        dup2(pipex.pipefd[READ], STDIN_FILENO);
        execve(file_path2, args2, envp);
    }

    return 0;
}


