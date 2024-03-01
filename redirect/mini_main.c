#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// in my wsl environment  i have to add compile option -lreadline

int	main(void)
{
    char	*line;

    rl_outstream = stderr;
    while (1)
    {
        line = readline("minishell$ ");
        if (line == NULL)
            break ;
        if (*line)
        {
            // printf("%s\n", line);
            add_history(line);
        }
        free(line);
    }
    exit(0);
}