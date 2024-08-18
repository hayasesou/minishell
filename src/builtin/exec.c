#include "minishell.h"

void exec_cmd(t_parser *parser, t_context *context)
{

    if(is_minishell_builtin(parser->cmd[0]) == true)
    {
        printf("self builtin\n");
        //todo;
        //implement self_builin
        return ;
    }
    else
        bash_builtin(parser, context);

    context->exit_status = COMMAND_NOT_FOUND;
    printf("Command '%s' not found\n", parser->cmd[0]);
    exit(COMMAND_NOT_FOUND);
}

#include <unistd.h>

// Example main function for demonstration
//./pipex cmd1 cmd2
int main(int ac, char **av, char **envp)
{
    t_context ctx;
    t_parser *parser_head;
    int i;

    ctx.env_head = env_init(envp);
    t_env *tmp_env = ctx.env_head->next;
    while(tmp_env != ctx.env_head)
    {
        printf("env_naem: %s\n", tmp_env->env_name);
        printf("env_value: %s\n", tmp_env->env_val);
        tmp_env = tmp_env->next;
    }
    if(ac < 2)
    {
        ft_putstr_fd("Usage: ./builtin cmd1 cmd2\n", 2);
        return 1;
    }
    parser_head = (t_parser *)malloc(sizeof(t_parser) * (ac - 1));
    i = 0;
    while (i < ac - 1)
    {

        parser_head[i].cmd = (char **)malloc(sizeof(char *) * 2);
        parser_head[i].cmd[0] = ft_strdup(av[i + 1]);
        parser_head[i].cmd[1] = NULL;
        parser_head[i].file = NULL;
        if (i == ac - 2)
            parser_head[i].next = NULL;
        else
            parser_head[i].next = &parser_head[i + 1];
        if (i == 0)
            parser_head[i].prev = NULL;
        else
            parser_head[i].prev = &parser_head[i - 1];
        i++;
    }

    
    // << eof > test2 > test3
    t_file f11;
    t_file f12;
    t_file f13;
    f11.file_name = "eof";
    f11.type = HEREDOC;
    f11.heredoc_fd = -1;
    f11.next = &f12;
    f12.file_name = "test2";
    f12.type = OUT_FILE;
    f12.heredoc_fd = -1;
    f12.next = &f13;
    f13.file_name = "test3";
    f13.type = OUT_FILE;
    f13.heredoc_fd = -1;
    f13.next = NULL;


    parser_head[0].file = &f11;

    

    
    exec_cmd(parser_head, &ctx);

    while(i > 0)
    {
        i--;
        free(parser_head[i].cmd[0]);
        free(parser_head[i].cmd);
    }
    free(parser_head);
    return 0;
}
