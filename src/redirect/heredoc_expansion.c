#include "minishell.h"


char  *heredoc_get_env_value(char *env_name, t_env *env_head, t_context *context, int *heredoc_status)
{
    char *env_value;
    t_env *tmp_env;

    if (env_head == NULL)
        return (NULL);
    tmp_env = env_head->next;
    while(tmp_env != env_head)
    {
        if(ft_strncmp(env_name, tmp_env->env_name, ft_strlen(env_name)) == 0 
            && ft_strlen(env_name) == ft_strlen(tmp_env->env_name))
        {
            env_value = ft_strdup(tmp_env->env_val);
            if(env_value == NULL)
            {
                context->exit_status = 1;
                *heredoc_status = 1;
                fatal_error("malloc error");
            }
            return (env_value);
        }
        tmp_env = tmp_env->next;
    }
    return (NULL);
}


static char *heredoc_join(char *brefore_env, char *env_value, char *after_env, size_t *current_index)
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

static char *make_heredoc_newline(char *line, size_t *i, t_context *context, int *heredoc_status)
{
    size_t j;
    char *env_value;
    char *before_env;
    char *after_env;
    char *env_name;

    j = 0;
    before_env = ft_substr(line, 0, *i -1);
    if(before_env == NULL)
    {
        context->exit_status = 1;
        *heredoc_status = 1;
        fatal_error("malloc error");
    }
    while(ft_isalnum(line[*i + j]) || line[*i + j] == '_')
        j++;
    after_env = ft_substr(line, *i +j, ft_strlen(line) - (*i + j));
    if(after_env == NULL)
    {
        free(before_env);
        context->exit_status = 1;
        *heredoc_status = 1;
        fatal_error("malloc error");
    }
    env_name = ft_substr(line, *i, j);
    if(env_name == NULL)
    {
        free(before_env);
        free(after_env);
        context->exit_status = 1;
        *heredoc_status = 1;
        fatal_error("malloc error");
    }
    env_value = ft_strdup(heredoc_get_env_value(env_name, context->env_head, context, heredoc_status));
    if(env_value == NULL)
    {
        free(before_env);
        free(after_env);
        free(env_name);
        context->exit_status = 1;
        *heredoc_status = 1;
        fatal_error("malloc error");
    }
    free(env_name);
    if(env_value == NULL)
        env_value = ft_strdup("");
    return (heredoc_join(before_env, env_value, after_env, i));
}

char *heredoc_expantion(char *line, t_context *context, int *heredoc_status)
{
    size_t i;
    char *new_line;

    i = 0;
    new_line = ft_strdup(line);
    if(new_line == NULL)
    {
        context->exit_status = 1;
        *heredoc_status = 1;
        fatal_error("malloc error");
    }
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
                new_line = make_heredoc_newline(new_line, &i, context, heredoc_status);
                if(new_line == NULL)
                    return NULL;
            }
        }
    }
    return new_line;
}