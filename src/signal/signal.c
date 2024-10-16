#include "minishell.h"

void set_signal_handler()
{
    struct sigaction sa;

    ft_memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
    sa.sa_handler = signal_handler;
    sigaction(SIGINT, &sa, NULL);
}

void    set_signal_parent_handler()
{
    struct sigaction    sa;

    ft_memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = signal_parent_handler;
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
}

void    set_signal_child_handler()
{
    struct sigaction sa;

    ft_memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = heredoc_signal_handler;
    sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
}

void set_heredoc_signal_handler()
{
    struct sigaction sa;

    ft_memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa, NULL);
}

void    signal_init(t_context *ctx)
{
    if (g_signal == 1 || g_signal == SIGINT)
        ctx->exit_status = 1;
    g_signal = 0;

    set_signal_handler();
}
