#include "minishell.h"

void no_arg_export(t_env *env_head)
{
    t_env *env_tmp;
    bool is_exit_oldpwd;

    is_exit_oldpwd = false;
    env_tmp = env_head->next;
    while(env_tmp != env_head)
    {
        if(ft_strncmp(env_tmp->env_name, "OLDPWD", ft_strlen(env_tmp->env_name)) == 0)
            is_exit_oldpwd = true;
        printf("declare -x %s", env_tmp->env_name);
        if(env_tmp->env_val != NULL)
            printf("=\"%s\"\n", env_tmp->env_val);
        else
            printf("\n");
        env_tmp = env_tmp->next;
    }
    if(is_exit_oldpwd == false)
        printf("declare -x OLDPWD\n");

}


//expected input: <env_name> , <env_name>= , <env_name>=<env_value>
void arg_export(t_env *env_head, char *arg, t_context *context)
{
    char *first_equal;

    first_equal = find_first_equal(arg);
    if(first_equal == NULL)
        return ;   
    else
    {
        char *env_value;
        char *env_name;

        env_name = ft_substr(arg, 0, first_equal - arg);
        if(*(first_equal + 1) == '\0')
            env_value = ft_strdup("");
        else
            env_value = ft_strdup(first_equal + 1);
        if(env_value == NULL)
            return ;
        set_env_value(env_name, env_value, env_head, context);
        free(env_value);
        free(env_name);
    }
}
