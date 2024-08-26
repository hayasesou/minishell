#include "minishell.h"

void free_command(char **cmd)
{
    int i;

    if (!cmd)
        return;

    i = 0;
    while (cmd[i])
    {
        free(cmd[i]);
        i++;
    }
    free(cmd);
}

// 新しいコマンドの追加、既存のコマンドの後ろに追加する
int add_command(t_parser *cur_arg, char *cmd_str)
{
    char **new_cmd;
    int i = 0;

    while (cur_arg->cmd && cur_arg->cmd[i])
        i++;
    new_cmd = (char **)malloc(sizeof(char *) * (i + 2));
    if (new_cmd == NULL)
        return (0);
    i = 0;
    while (cur_arg->cmd && cur_arg->cmd[i])
    {
        new_cmd[i] = ft_strdup(cur_arg->cmd[i]);
        if (!new_cmd[i])
        {
            free_command(new_cmd);
            return (0);
        }
        i++;
    }
    new_cmd[i] = ft_strdup(cmd_str);
    if (!new_cmd[i])
    {
        free_command(new_cmd);
        return (0);
    }
    new_cmd[i + 1] = NULL;
    free_command(cur_arg->cmd);
    cur_arg->cmd = new_cmd;
    return (1);
}

// 連続する文字列トークンを1つの文字列に結合する,スペース有無で結合するか判断
static char *combine_words(t_token **token_tmp)
{
    char *combined_str;
    char *temp;

    combined_str = NULL;
    if (!*token_tmp)
        return (NULL);
    combined_str = ft_strdup((*token_tmp)->data);
    if (!combined_str)
        return (NULL);
    *token_tmp = (*token_tmp)->next;
    while (*token_tmp && is_not_space_string(*token_tmp))
    {
        temp = ft_strjoin(combined_str, (*token_tmp)->data);
        if (!temp)
        {
            free(combined_str);
            return (NULL);
        }
        free(combined_str);
        combined_str = temp;
        *token_tmp = (*token_tmp)->next;
    }
    return (combined_str);
}

// 文字列を結合するものはしてからコマンドとして追加するための判断をする？ための関数（日本語むずい）25行超えたから分割
static int add_words_command(t_parser *cur_arg, t_token **token_tmp)
{
    char *combined_str;
    
    combined_str = combine_words(token_tmp);
    if (!combined_str)
        return (0);
    if (!add_command(cur_arg, combined_str))
    {
        free(combined_str);
        return (0);
    }
    free(combined_str);
    return (1);
}

void create_command(t_parser *args, t_token *token)
{
    t_token *token_tmp;
    t_parser *cur_arg;

    token_tmp = token;
    cur_arg = args;
    while (token_tmp && token_tmp->type != TK_EOF && token_tmp->type != TK_PIPE)
    {
        if (is_redirect(token_tmp))
        {
            if (!add_redirect(cur_arg, token_tmp))
                return ;
            token_tmp = token_tmp->next->next;
        }
        else if (is_string(token_tmp))
        {
            if (!add_words_command(cur_arg, &token_tmp))
                return ;
        }
        else
            token_tmp = token_tmp->next;
    }
}
