#include "../../include/minishell.h"

void sigint_handler(int signum, siginfo_t *info, void *ucontext)
{
    (void)signum;
    (void)ucontext;
    (void)info;
    g_signal = SIGINT;
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void sigquit_handler(int signum, siginfo_t *info, void *ucontext)
{
    (void)signum;
    (void)ucontext;
    (void)info;
//    g_signal = SIGQUIT;
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


//親プロセス子プロセスの実装について
//シェルのようなプログラムでは、親プロセス（シェル本体）と子プロセス（実行されるコマンド）で異なるシグナルハンドラの動作が必要となることが多い
//
//親プロセス（シェル）のシグナルハンドラ
//SIGINT（Ctrl+C）: ユーザーがCtrl+Cを押したときに、現在の入力行をキャンセルして新しいプロンプトを表示する。
//SIGQUIT（Ctrl+\）: 通常は無視するか、特定の動作を行う。
//
//子プロセス（実行されるコマンド）のシグナルハンドラ
//シェルが実行する外部コマンドは、通常のシグナル動作を期待します。つまり、SIGINTやSIGQUITを受け取ったときにデフォルトの動作（プロセスの終了など）を行います。
//→シグナルハンドラをデフォルトにリセットする必要がある

//heredocにおけるシグナルハンドラ
//heredocはシェルでの入力リダイレクトの一種で、ユーザーから特定のデリミタが入力されるまで継続的に入力
//
//heredocの実装方法によっては、シェルがforkして子プロセスでheredocの入力を処理する場合がある
//heredocの親プロセス
//SIGINT（Ctrl+C）: 子プロセスにSIGINTを送信し、heredocの入力をキャンセルします。
//SIGQUIT: 無視するか、特定の動作を行う。
//heredocの子プロセス
//SIGINT（Ctrl+C）: heredocの入力を終了し、適切なクリーンアップを行って子プロセスを終了します。
//SIGQUIT: 無視するか、デフォルトの動作を行う。
//