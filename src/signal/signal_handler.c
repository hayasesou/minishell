#include "minishell.h"

void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        g_signal = 1;
        ft_printf("\n");
        rl_on_new_line();
//        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void signal_parent_handler(int signum)
{
    if (signum == SIGINT)
    {
        g_signal = signum;
        ft_printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    if (signum == SIGQUIT)
    {
        g_signal = signum;
        ft_printf("Quit: 3\n");
//        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void    heredoc_signal_parent_handler(int signum)
{
    if (signum == SIGINT)
    {
        g_signal = 1;
        ft_printf("\n");
    }
}
