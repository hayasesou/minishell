#include "../../include/minishell.h"

int g_signal = 0;

void sigint_handler(int signum, siginfo_t *info, void *ucontext)
{
    (void)signum;
    (void)ucontext;
    (void)info;
    g_signal = SIGINT;
    printf("sigint\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void sigquit_handler(int signum, siginfo_t *info, void *ucontext)
{
    (void)signum;
    (void)ucontext;
    (void)info;
    g_signal = SIGQUIT;
    printf("sigquit\n");
    rl_on_new_line();
    rl_redisplay();
}

void signal_init(t_context *ctx)
{
    struct sigaction sigint_act;
    struct sigaction sigquit_act;

    if (g_signal == 1 || g_signal == SIGINT)
        ctx->exit_status = 1;
    g_signal = 0;

    sigemptyset(&sigint_act.sa_mask);
    sigaddset(&sigint_act.sa_mask, SIGINT); //これはいらない？SIGINTはブロックされる用に設定される
    sigint_act.sa_sigaction = sigint_handler;
    sigint_act.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sigint_act, NULL);

    sigemptyset(&sigquit_act.sa_mask);
    sigaddset(&sigquit_act.sa_mask, SIGQUIT);
    sigquit_act.sa_sigaction = sigquit_handler;
    sigquit_act.sa_flags = SA_SIGINFO;
    sigaction(SIGQUIT, &sigquit_act, NULL);
}

// signal flagは何があるか
//0: デフォルト、何も指定しない時に使用
//SA_RESTART: シグナルハンドラが終了した後に中断したシステムコールを自動的に再実行するフラグ
//             例えばread(), write()などのシステムコールが中断された場合、シグナルハンドラが終了した後に自動的に再実行される
//             シェルではユーザーの入力が中断されないようにするために設定する
//SA_SIGINFO:　シグナルハンドラに追加情報が渡される、ハンドラ関数が引数を持ち定義されて売り場合に使う

