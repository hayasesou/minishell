#include "../../include/minishell.h"

static bool    is_exit_null(char **list)
{
    if (list[1] == NULL)
        return (true);
    if (ft_strcmp(list[1], "--") == 0 && list[2] == NULL) //strcmp作ってないかも
        return (true);
    return (false);
}


void    free_exit(char **list, t_context *context)
{
    free_all(context);
    exit(context->exit_status);
}

static bool    is_exit_status(char *str)
{
    int    i;

    i = 0;
    if (str[0] == '+' || str[0] == '-')
        i++;
    if (!str[i])
        return false;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return false;
        i++;
    }
    return true;
}

//オーバーフローや"+"や"-"のみの入力をチェックする処理
static bool    is_exit_code(char *num, t_context *context)
{
    int    exit_code;

    if (is_exit_code(num, context))
        fatal_error("exit", "numeric argument required");
    else
    {
        exit_code = ft_atoi(num);
        free_exit(line, context);
        if (exit_code < 0)
        {
            while (exit_code < 0)
                exit_code += 256;
        }
        if (exit_code > 255)
            exit_code %= 256;
        context->exit_status = exit_code;
        exit(exit_code);
    }
}

statuc void    excute_exit(char *num, char **line, t_context *context)
{
    int    exit_code;

    if (is_exit_code(num, context))
        fatal_error("exit", "numeric argument required");
    else
    {
        exit_code = ft_atoi(num);
        free_exit(line, context);
        if (exit_code < 0)
        {
            while (exit_code < 0)
                exit_code += 256;
        }
        if (exit_code > 255)
            exit_code %= 256;
//        if (type == PARENT)
//            ft_puterr("exit\n");
        context->exit_status = exit_code;
        exit(exit_code);
    }
}

static void    exit_main(char **list, t_context *context)
{
    if (!is_exit_status(list[1]))
        fatal_error("exit", "numeric argument required");
    if (list[2] != NULL)
        fatal_error("exit", "too many arguments");
    else
        excute_exit();
}

void	exit_builtin(t_parser *parser, t_context *context)
{
    t_env    *env_tmp;
    char     **list;

    env_tmp = context->env_head->next;
    list = parser->cmd;
    if (is_exit_null(list) == false)
        free_exit(parser->cmd, context->env_head);
//    if (ft_strchr(list[1], ' '))
//    {
//        list = ft_split(parser->cmd, ' ');
//        if (list == NULL)
//            exit(1);
//        if (list[0] == NULL || list[1] != NULL)
//            exit_main(parser->cmd, context);
//        else
//        {
//            // TODO: exit_include_space
//        }
//    }
    else
        exit_main(parser->cmd, context);
}
