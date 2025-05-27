#include "../../inc/builtins.h"



// // Fonction find_env_index réécrite sans opérateur ternaire
// static int find_env_index(char **envp, const char *name)
// {
//     size_t i;
//     size_t name_len;
//     size_t current_len;
//     char *equal_sign;
    
//     name_len = ft_strlen(name);
//     i = 0;
//     while (envp[i])
//     {
//         equal_sign = ft_strchr(envp[i], '=');
//         if (equal_sign)
//             current_len = (size_t)(equal_sign - envp[i]);
//         else
//             current_len = ft_strlen(envp[i]);
            
//         if (ft_strncmp(envp[i], name, name_len) == 0 && current_len == name_len)
//             return ((int)i);
//         i++;
//     }
//     return (-1);
// }

// // Fonction env_set_existing réécrite sans opérateur ternaire
// static int env_set_existing(t_env *env, char *var, char *name, char *equal_sign)
// {
//     int i;
//     char *existing_equal;
//     size_t name_len;
    
//     i = 0;
//     while (env->envp[i])
//     {
//         existing_equal = ft_strchr(env->envp[i], '=');
//         if (existing_equal)
//             name_len = (size_t)(existing_equal - env->envp[i]);
//         else
//             name_len = ft_strlen(env->envp[i]);
            
//         if (ft_strncmp(env->envp[i], name, name_len) == 0 && ft_strlen(name) == name_len)
//         {
//             if (equal_sign)
//             {
//                 free(env->envp[i]);
//                 env->envp[i] = ft_strdup(var);
//             }
//             return (1);
//         }
//         i++;
//     }
//     return (0);
// }

// // Fonction env_add_new réécrite sans opérateur ternaire
// static int env_add_new(t_env *env, char *var, char *name, char *equal_sign)
// {
//     int i;
//     int j;
//     char **new_envp;
    
//     i = 0;
//     while (env->envp[i])
//         i++;
        
//     new_envp = malloc(sizeof(char *) * (i + 2));
//     if (!new_envp)
//         return (0);
        
//     j = 0;
//     while (j < i)
//     {
//         new_envp[j] = env->envp[j];
//         j++;
//     }
    
//     if (equal_sign)
//         new_envp[i] = ft_strdup(var);
//     else
//         new_envp[i] = ft_strdup(name);
        
//     new_envp[i + 1] = NULL;
//     free(env->envp);
//     env->envp = new_envp;
//     return (1);
// }

// // Fonction utilitaire pour valider les valeurs numériques de SHLVL
// static int is_valid_shlvl_value(const char *str)
// {
//     int i = 0;
    
//     if (!str)
//         return 0;
        
//     if (str[0] == '-' || str[0] == '+')
//         i = 1;
        
//     if (!str[i]) // Juste un signe
//         return 0;
        
//     while (str[i])
//     {
//         if (!ft_isdigit(str[i]))
//             return 0;
//         i++;
//     }
//     return 1;
// }

// Version améliorée de ft_atoi pour SHLVL avec gestion des cas limites
static int shlvl_atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    
    if (!str)
        return 0;
        
    if (str[0] == '-')
    {
        sign = -1;
        i = 1;
    }
    else if (str[0] == '+')
    {
        i = 1;
    }
    
    while (str[i] && ft_isdigit(str[i]))
    {
        // Protection contre les débordements
        if (result > (2147483647 - (str[i] - '0')) / 10)
        {
            if (sign == 1)
                return 2147483647;
            else
                return -2147483648;
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}

void increment_shlvl(t_env *env)
{
    char *value = env_get(env, "SHLVL");
    int shlvl = 0;
    char *new_value;
    char *shlvl_var;
    
    if (value)
    {
        shlvl = shlvl_atoi(value);
        // Bash traite les valeurs non-numériques comme 0
        // et les valeurs négatives comme étant réinitialisées à 0
        if (shlvl < 0)
            shlvl = 0;
    }
    
    shlvl++;
    
    // Bash limite SHLVL à 1000 pour éviter les débordements
    if (shlvl > 1000)
        shlvl = 1;
    
    new_value = ft_itoa(shlvl);
    if (!new_value)
        return;
    
    // Créer la chaîne complète "SHLVL=valeur"
    shlvl_var = ft_strjoin("SHLVL=", new_value);
    free(new_value);
    if (!shlvl_var)
        return;
    
    // Utiliser env_set normale mais améliorer la logique
    env_set(env, shlvl_var);
    
    free(shlvl_var);
}