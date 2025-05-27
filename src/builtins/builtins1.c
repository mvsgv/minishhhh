#include "../../inc/builtins.h"

int builtin_echo(char **args)
{
    int i;
    int n_option;
    int j;

    i = 1;
    n_option = 0;
    j = 2;
    if (args[1] && args[1][0] == '-' && args[1][1] == 'n')
    {
        while (args[1][j] == 'n')
            j++;
        if (args[1][j] == '\0')
        {
            n_option = 1;
            i = 2;
        }
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (!n_option)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return (0);
}

static char *get_cd_path(char **args, t_env *env)
{
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        if (!env->home)
        {
            ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
            return (NULL);
        }
        return (env->home);
    }
    return (args[1]);
}

int builtin_cd(char **args, t_env *env)
{
    char *path;
    char old_pwd[1024];

    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
    {
        perror("cd: getcwd error");
        return (1);
    }
    path = get_cd_path(args, env);
    if (!path)
        return (1);
    if (chdir(path) != 0)
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        perror(path);
        return (1);
    }
    return (0);
}

int builtin_pwd(void)
{
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) == NULL) 
    {                                                                              //F
        perror("pwd");
        return (1);
    }
    ft_putstr_fd(cwd, STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
    return (0);
}

int builtin_exit(char **args)
{
    int exit_code;
    int i;

    exit_code = 0;
    if (args[1]) 
    {
        i = 0;
        while (args[1][i]) 
        {
            if (!ft_isdigit(args[1][i])) 
            {
                ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
                exit(255);
            }
            i++;
        }
        exit_code = ft_atoi(args[1]);
        if (args[2]) 
        {
            ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
            return (1);
        }
    }
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    exit(exit_code);
}