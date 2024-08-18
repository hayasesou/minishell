#include "minishell.h"

void exec_cmd(t_parser *parser, t_context *context)
{
    (void)parser;
    (void)context;
    char *path = getenv("PATH");
    printf("%s\n", path);
}

int main(void)
{
    t_parser *parser;
    t_context context;

    parser = NULL;
    exec_cmd(parser, &context);
    return 0;
}
