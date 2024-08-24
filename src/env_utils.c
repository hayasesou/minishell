#include "minishell.h"


static char* env_join(char *env_name, char *env_value, t_context *context)
{
    char *tmp_str;
    char *env_str;

    tmp_str = ft_strjoin(env_name, "=");
    if(tmp_str == NULL)
    {
        context->exit_status = NORMAL_ERROR;
        return (NULL);
    }
    env_str = ft_strjoin(tmp_str, env_value);
    free(tmp_str);
    return (env_str);
}


char ** make_env_list(t_env *env_head, t_context *context)
{
    t_env *env_tmp;
    char **env_list;
    int count;
    int i;

    count = 0;
    env_tmp = env_head->next;
    while(env_tmp != env_head)
    {
        count++;
        env_tmp = env_tmp->next;
    }
    env_list = (char **)malloc(sizeof(char *) * (count + 1));
    env_tmp = env_head->next;
    i = 0;
    while(i < count)
    {
        env_list[i] = env_join(env_tmp->env_name, env_tmp->env_val, context);
        if(env_list[i] == NULL)
        {
            while(i >= 0)
            {
                free(env_list[i]);
                i--;
            }
            free(env_list);
            context->exit_status = NORMAL_ERROR;
            return (NULL);
        }
        env_tmp = env_tmp->next;
        i++;
    }
    env_list[i] = NULL;
    
    return (env_list);
}


void free_env_list(char**env_list)
{
    int i;

    i = 0;
    while(env_list[i] != NULL)
    {
        free(env_list[i]);
        i++;
    }
    free(env_list);
}


void free_all_env_node(t_env *env_head)
{
    t_env *env_tmp;
    t_env *env_tmp2;

    env_tmp = env_head->next;
    while(env_tmp != env_head)
    {
        free(env_tmp->env_name);
        free(env_tmp->env_val);
        env_tmp2 = env_tmp;
        env_tmp = env_tmp->next;
        free(env_tmp2);
    }
    free(env_head);
}


char *get_env_value(char *env_name, t_env *env_head)
{
    t_env *env_tmp;

    env_tmp = env_head->next;
    while(env_tmp != env_head)
    {
        if((ft_strncmp(env_tmp->env_name, env_name, ft_strlen(env_name)) == 0) && (env_tmp->env_name[ft_strlen(env_name)] == '\0'))
            return (env_tmp->env_val);
        env_tmp = env_tmp->next;
    }
    return (NULL);
}

void set_env_value(char *env_name, char *new_env_value, t_env *env_head, t_context *context)
{
    t_env *env_tmp;

    env_tmp = env_head->next;
    while(env_tmp != env_head)
    {
        if((ft_strncmp(env_tmp->env_name, env_name, ft_strlen(env_name)) == 0) && (env_tmp->env_name[ft_strlen(env_name)] == '\0'))
        {
            free(env_tmp->env_val);
            env_tmp->env_val = ft_strdup(new_env_value);
            if(env_tmp->env_val == NULL)
            {
                context->exit_status = NORMAL_ERROR;
                perror("minishell setenv");
                return ;
            }
            return ;
        }
        env_tmp = env_tmp->next;
    }
}