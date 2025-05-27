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

bool is_valid_identifier(const char *str)
{
    int i;
    
    i = 0;
    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (false);
    i = 1;
    while (str[i] && str[i] != '=') 
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (false);
        i++;
    }
    return (true);
}