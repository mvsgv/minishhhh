#include "../../inc/builtins.h"


//ECHO

static int is_valid_n_option(char *arg)
{
    int i;

    if (arg[0] != '-' || arg[1] != 'n')
        return (0);
    i = 2;
    while (arg[i] == 'n')
        i++;
    return (arg[i] == '\0');
}

int builtin_echo(char **args)
{
    int i;
    int n_option;

    i = 1;
    n_option = 0;
    while (args[i] && is_valid_n_option(args[i]))
    {
        n_option = 1;
        i++;
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

//CD 

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

static int update_pwd_oldpwd(t_env *env, char *old_pwd)
{
    char *tmp;

    tmp = ft_strjoin("OLDPWD=", old_pwd);
    if (!tmp)
        return (1);
    env_set(env, tmp);
    free(tmp);

    if (getcwd(old_pwd, 1024) == NULL)
    {
        perror("cd: getcwd error");
        return (1);
    }

    tmp = ft_strjoin("PWD=", old_pwd);
    if (!tmp)
        return (1);
    env_set(env, tmp);
    free(tmp);

    return (0);
}

static char *handle_cd_dash(t_env *env)
{
    char *path;

    path = env_get(env, "OLDPWD");
    if (!path)
    {
        ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
        return (NULL);
    }
    ft_putstr_fd(path, STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
    return (path);
}

int builtin_cd(char **args, t_env *env)
{
    char old_pwd[1024];
    char *path;

    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
    {
        perror("cd: getcwd error");
        return (1);
    }
    if (args[1] && ft_strcmp(args[1], "-") == 0)
        path = handle_cd_dash(env);
    else
        path = get_cd_path(args, env);
    if (!path || chdir(path) != 0)
    {
        if (path)
        {
            ft_putstr_fd("cd: ", STDERR_FILENO);
            perror(path);
        }
        return (1);
    }
    return (update_pwd_oldpwd(env, old_pwd));
}

//PWD

int builtin_pwd(t_env *env)
{
    char *pwd_env;

    pwd_env = env_get(env, "PWD");
    if (pwd_env)
    {
        ft_putstr_fd(pwd_env, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        return (0);
    }
    else
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("pwd");
            return (1);
        }
        ft_putstr_fd(cwd, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        return (0);
    }
}
//EXIT

static int is_numeric(const char *str)
{
    int i = 0;

    if (str[i] == '+' || str[i] == '-')
        i++;
    if (str[i] == '\0')
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int builtin_exit(char **args)
{
    int exit_code;

    if (args[1])
    {
        if (!is_numeric(args[1]))
        {
            ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
            exit(255);
        }
        if (args[2])
        {
            ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
            return (1);
        }
        exit_code = (unsigned char)ft_atoi(args[1]);
    }
    else
        exit_code = 0;

    ft_putstr_fd("exit\n", STDOUT_FILENO);
    exit(exit_code);
}
