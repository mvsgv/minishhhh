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
