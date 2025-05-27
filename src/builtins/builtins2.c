#include "../../inc/builtins.h"

static void print_export_var(char *var)
{
    char *equal_sign;

    ft_putstr_fd("declare -x ", STDOUT_FILENO);
    equal_sign = ft_strchr(var, '=');
    if (equal_sign)
    {
        write(STDOUT_FILENO, var, equal_sign - var);
        ft_putstr_fd("=\"", STDOUT_FILENO);
        ft_putstr_fd(equal_sign + 1, STDOUT_FILENO);
        ft_putstr_fd("\"\n", STDOUT_FILENO);
    }
    else
    {
        ft_putstr_fd(var, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
}

static int export_no_args(t_env *env)
{
    int i;
    char **envp_copy;

    envp_copy = ft_arrdup(env->envp);
    if (!envp_copy)
        return (1);
    ft_sort_strarr(envp_copy);
    i = 0;
    while (envp_copy[i])
    {
        print_export_var(envp_copy[i]);
        i++;
    }
    ft_free_arr(envp_copy);
    return (0);
}

int builtin_export(char **args, t_env *env)
{
    int i;

    i = 1;
    if (!args[1])
        return (export_no_args(env));
    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            ft_putstr_fd("export: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            i++;
            continue;
        }
        env_set(env, args[i]);
        i++;
    }
    return (0);
}

int builtin_unset(char **args, t_env *env)
{
    int i;

    i = 1;    
    while (args[i]) 
    {
        if (!is_valid_identifier(args[i])) 
        {
            ft_putstr_fd("unset: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            i++;
            continue;
        }
        env_unset(env, args[i]);
        i++;
    }
    return (0);
}

int builtin_env(t_env *env)
{
    int i;

    i = 0;    
    while (env->envp[i]) 
    {
        ft_putstr_fd(env->envp[i], STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        i++;
    }
    return (0);
}