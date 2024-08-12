#include "minishell.h"


char  *get_env_value(char *env_name, t_context *context)
{
    //tentative implementation
    char *env_value;

    env_value = ft_strdup("value");
    return (env_value);
}


char *heredoc_join(char *brefore_env, char *env_value, char *after_env, size_t *current_index)
{
    char *new_line;
    char *tmp;
    size_t next_index;

    next_index = ft_strlen(brefore_env) + ft_strlen(env_value);
    tmp = ft_strjoin(brefore_env, env_value);
    free(brefore_env);
    free(env_value);
    if(tmp == NULL)
    {
        free(after_env);
        return NULL;
    }
    new_line = ft_strjoin(tmp, after_env);
    free(tmp);
    free(after_env);
    if (new_line == NULL)
        return NULL;
    *current_index = next_index;
    return new_line;
}

char *make_heredoc_newline(char *line, size_t *i, t_context *context)
{
    size_t j;

    j = 0;
    //malloc before_env
    char *before_env = ft_substr(line, 0, *i -1);
    if(before_env == NULL)
        fatal_error("malloc error");
    while(ft_isalnum(line[*i + j]) || line[*i + j] == '_')
        j++;
    //malloc after_env
    char *after_env = ft_substr(line, *i +j, ft_strlen(line) - (*i + j));
    if(after_env == NULL)
    {
        free(before_env);
        fatal_error("malloc error");
    }
    //malloc env_name
    char *env_name = ft_substr(line, *i, j);
    if(env_name == NULL)
    {
        free(before_env);
        free(after_env);
        fatal_error("malloc error");
    }
    //malloc env_value
    char *env_value = ft_strdup(get_env_value(env_name, context));
    //free env_name
    free(env_name);
    if(env_value == NULL)
        env_value = ft_strdup("");
    return (heredoc_join(before_env, env_value, after_env, i));
}

char *heredoc_expantion(char *line, t_context *context)
{
    size_t i;
    char *new_line;

    i = 0;
    new_line = ft_strdup(line);
    free(line);
    while(new_line[i] != '\0')
    {
        if (new_line[i++] == '$')
        {
            if(new_line[i] == '\0')
                break;
            else if(new_line[i] == '$')
                continue;
            else
            {
                new_line = make_heredoc_newline(new_line, &i, context);
                if(new_line == NULL)
                    return NULL;
            }
        }
    }
    return new_line;
}