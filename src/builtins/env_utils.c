#include "../../inc/builtins.h"

char *env_get(t_env *env, const char *name)
{
    int i;
    int name_len;
    

    i = 0;
    name_len = ft_strlen(name);
    while (env->envp[i]) 
    {
        if (ft_strncmp(env->envp[i], name, name_len) == 0 && env->envp[i][name_len] == '=')
            return env->envp[i] + name_len + 1;
        i++;
    }
    return (NULL);
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

