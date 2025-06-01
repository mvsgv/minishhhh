#include "../../inc/builtins.h"

void set_var_with_value(t_env *env, char *var, char *name, char *equal_sign)
{
    if (env_set_existing(env, var, name, equal_sign))
    {
        update_home_if_needed(env, name, equal_sign + 1);
        return ;
    }
    env_add_new(env, var, name, equal_sign);
    update_home_if_needed(env, name, equal_sign + 1);
}

void set_var_without_value(t_env *env, char *name)
{
    char *new_var;

    if (!env_get(env, name))
    {
        new_var = ft_strjoin(name, "=");
        if (new_var)
        {
            env_add_new(env, new_var, name, NULL);
            free(new_var);
        }
    }
}

void env_set(t_env *env, char *var)
{
    char *name;
    char *equal_sign;

    equal_sign = ft_strchr(var, '=');
    if (equal_sign)
        name = ft_substr(var, 0, equal_sign - var);
    else
        name = ft_strdup(var);
    if (!name)
        return;

    if (equal_sign)
        set_var_with_value(env, var, name, equal_sign);
    else
        set_var_without_value(env, name);

    free(name);
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


