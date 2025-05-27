#include "../../inc/builtins.h"

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

// void env_set(t_env *env, char *var)
// {
//     char *name;
//     char *equal_sign;

//     equal_sign = ft_strchr(var, '=');
//     name = equal_sign ? ft_substr(var, 0, equal_sign - var) : ft_strdup(var);
//     if (!name)
//         return ;
//     if (env_set_existing(env, var, name, equal_sign))
//     {
//         free(name);
//         return ;
//     }
//     if (equal_sign || !env_get(env, name))
//         env_add_new(env, var, name, equal_sign);
//     if (equal_sign && ft_strcmp(name, "HOME") == 0)
//     {
//         free(env->home);
//         env->home = ft_strdup(equal_sign + 1);
//     }
//     free(name);
// }


void env_set(t_env *env, char *var)
{
    char *name;
    char *equal_sign;
    
    equal_sign = ft_strchr(var, '=');
    
    // Extraire le nom de la variable
    if (equal_sign)
        name = ft_substr(var, 0, equal_sign - var);
    else
        name = ft_strdup(var);
        
    if (!name)
        return;
    
    // Si on a une valeur (avec =)
    if (equal_sign)
    {
        // Toujours essayer de mettre à jour une variable existante
        if (env_set_existing(env, var, name, equal_sign))
        {
            // Mise à jour spéciale pour HOME après modification
            if (ft_strcmp(name, "HOME") == 0)
            {
                free(env->home);
                env->home = ft_strdup(equal_sign + 1);
            }
            free(name);
            return;
        }
        // Si pas trouvée, l'ajouter
        env_add_new(env, var, name, equal_sign);
        
        // Mise à jour spéciale pour HOME après ajout
        if (ft_strcmp(name, "HOME") == 0)
        {
            free(env->home);
            env->home = ft_strdup(equal_sign + 1);
        }
    }
    else
    {
        // Sans valeur, ne créer que si la variable n'existe pas déjà
        if (!env_get(env, name))
            env_add_new(env, var, name, equal_sign);
    }
    
    free(name);
}

static int find_env_index(char **envp, const char *name)
{
    size_t i;
    size_t name_len;
    size_t current_len;
    char *equal_sign;

    name_len = ft_strlen(name);
    i = 0;
    while (envp[i])
    {
        equal_sign = ft_strchr(envp[i], '=');
        if (equal_sign)
            current_len = (size_t)(equal_sign - envp[i]);
        else
            current_len = ft_strlen(envp[i]);

        if (ft_strncmp(envp[i], name, name_len) == 0 && current_len == name_len)
            return ((int)i);
        i++;
    }
    return (-1);
}


void env_unset(t_env *env, const char *name)
{
    int i;

    i = find_env_index(env->envp, name);
    if (i < 0)
        return ;
    free(env->envp[i]);
    while (env->envp[i + 1])
    {
        env->envp[i] = env->envp[i + 1];
        i++;
    }
    env->envp[i] = NULL;
    if (ft_strcmp(name, "HOME") == 0)
    {
        free(env->home);
        env->home = NULL;
    }
}