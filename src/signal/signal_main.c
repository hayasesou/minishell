#include "minishell.h"

int g_signal;

void sigint_handler(int sig)
{
    ft_printf("\n");
}

void sigquit_handler(int sig)
{
    ft_printf("sigquit\n");
}

void signal_init(t_context *ctx)
{
    struct sigaction sigint_act;
    struct sigaction sigquit_act;

    if (g_signal == 1 || g_signal == SIGINT)
        ctx->exit_status = 1;
    g_signal = 0;

    sigemptyset(&sigint_act.sa_mask);
    sigint_act.sa_sigaction = sigint_handler;
    sigint_act.sa_flags = SA_????; //何にすればいい？
    sigaction(SIGINT, &sigint_act, NULL);

    sigemptyset(&sigquit_act.sa_mask);
    sigquit_act.sa_sigaction = sigquit_handler;
    sigquit_act.sa_flags = SA_????; //何にすればいい？
    sigaction(SIGQUIT, &sigquit_act, NULL);
}
