#include "../../inc/builtins.h"


// SET

static int env_set_existing(t_env *env, char *var, char *name, char *equal_sign)
{
    int i;
    char *existing_equal;
    size_t name_len;

    i = 0;
    while (env->envp[i])
    {
        existing_equal = ft_strchr(env->envp[i], '=');
        name_len = existing_equal ? (size_t)(existing_equal - env->envp[i]) : ft_strlen(env->envp[i]);
        if (ft_strncmp(env->envp[i], name, name_len) == 0 && ft_strlen(name) == name_len)
        {
            if (equal_sign)
            {
                free(env->envp[i]);
                env->envp[i] = ft_strdup(var);
            }
            return (1);
        }
        i++;
    }
    return (0);
}

static int env_add_new(t_env *env, char *var, char *name, char *equal_sign)
{
    int i;
    int j;
    char **new_envp;

    i = 0;
    while (env->envp[i])
        i++;
    new_envp = malloc(sizeof(char *) * (i + 2));
    if (!new_envp)
        return (0);
    j = 0;
    while (j < i)
    {
        new_envp[j] = env->envp[j];
        j++;
    }
    new_envp[i] = equal_sign ? ft_strdup(var) : ft_strdup(name);
    new_envp[i + 1] = NULL;
    free(env->envp);
    env->envp = new_envp;
    return (1);
}

static void update_home_if_needed(t_env *env, char *name, char *value)
{
    if (ft_strcmp(name, "HOME") == 0)
    {
        free(env->home);
        env->home = ft_strdup(value);
    }
}

static void set_var_with_value(t_env *env, char *var, char *name, char *equal_sign)
{
    if (env_set_existing(env, var, name, equal_sign))
    {
        update_home_if_needed(env, name, equal_sign + 1);
        return;
    }
    env_add_new(env, var, name, equal_sign);
    update_home_if_needed(env, name, equal_sign + 1);
}

static void set_var_without_value(t_env *env, char *name)
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

