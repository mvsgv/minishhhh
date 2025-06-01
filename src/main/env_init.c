#include "../../inc/builtins.h"

void env_free(t_env *env)
{
    if (!env)
        return ;
    if (env->envp)
        ft_free_arr(env->envp);
    if (env->home)
        free(env->home);
    free(env);
}

//SHLVL

static int sanitize_shlvl(int shlvl)
{
    if (shlvl < 0)
        return 0;
    if (shlvl > 1000)
        return 1;
    return shlvl;
}

void increment_shlvl(t_env *env)
{
    char *value;
    int shlvl;
    char *new_value;
    char *shlvl_var;

    value = env_get(env, "SHLVL");
    if (value)
        shlvl = ft_atoi(value);
    else
        shlvl = 0;
    shlvl = sanitize_shlvl(shlvl);
    shlvl++;
    new_value = ft_itoa(shlvl);
    if (!new_value)
        return;
    shlvl_var = ft_strjoin("SHLVL=", new_value);
    free(new_value);
    if (!shlvl_var)
        return;
    env_set(env, shlvl_var);
    free(shlvl_var);
}

char **ft_arrdup(char **arr)
{
    int i;
    int len;
    char **dup;
    
    i = 0;
    len = 0;
    while (arr[len])
        len++;
    dup = malloc(sizeof(char *) * (len + 1));
    if (!dup)
        return (NULL);
    while (i < len) 
    {
        dup[i] = ft_strdup(arr[i]);
        if (!dup[i]) 
        {
            while (--i >= 0)
                free(dup[i]);
            free(dup);
            return (NULL);
        }
        i++;
    }
    dup[len] = NULL;
    return (dup);
}

t_env *env_init(char **envp)
{
    t_env *env;
    
    env = malloc(sizeof(t_env));
    if (!env)
        return (NULL);
    env->envp = ft_arrdup(envp);
    if (!env->envp) 
    {
        free(env);
        return (NULL);
    }
    increment_shlvl(env);
    env->exit_status = 0;
    env->home = env_get(env, "HOME");
    if (env->home)
        env->home = ft_strdup(env->home);
    return (env);
}
