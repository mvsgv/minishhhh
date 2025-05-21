#include "../../inc/builtins.h"






char *expand_variables(char *arg, t_env *env)
{
	char	*result = calloc(1, sizeof(char));
	size_t	i = 0, j;
	if (!result)
		return (NULL);

	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] &&
			(ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'))
		{
			i++;
			j = i;
			while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_'))
				j++;
			char *var_name = strndup(arg + i, j - i);
			char *var_value = env_get(env, var_name);
			if (!var_value)
				var_value = ""; // variable non définie → chaîne vide

			// concatène result + var_value
			char *tmp = malloc(strlen(result) + strlen(var_value) + 1);
			if (!tmp)
				return (free(var_name), free(result), NULL);
			tmp[0] = '\0';
			strcat(tmp, result);
			strcat(tmp, var_value);
			free(result);
			result = tmp;
			free(var_name);
			i = j;
		}
		else
		{
			char buf[2] = { arg[i], '\0' };
			char *tmp = malloc(strlen(result) + 2);
			if (!tmp)
				return (free(result), NULL);
			tmp[0] = '\0';
			strcat(tmp, result);
			strcat(tmp, buf);
			free(result);
			result = tmp;
			i++;
		}
	}
	return (result);
}
// int builtin_echo(char **args, t_env *env)
// {
// 	int	i = 1;
// 	int	n_option = 0;

// 	if (args[1] && args[1][0] == '-' && args[1][1] == 'n')
// 	{
// 		int	j = 2;
// 		while (args[1][j] == 'n')
// 			j++;
// 		if (args[1][j] == '\0')
// 		{
// 			n_option = 1;
// 			i = 2;
// 		}
// 	}

// 	while (args[i])
// 	{
// 		char *expanded = expand_variables(args[i], env);
// 		if (expanded)
// 		{
// 			ft_putstr_fd(expanded, STDOUT_FILENO);
// 			free(expanded);
// 		}
// 		if (args[i + 1])
// 			ft_putchar_fd(' ', STDOUT_FILENO);
// 		i++;
// 	}
// 	if (!n_option)
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 	return (0);
// }






int builtin_echo(char **args, t_env *env)
{
    int i = 1;
    int n_option = 0;

    if (args[1] && args[1][0] == '-' && args[1][1] == 'n')
    {
        int j = 2;
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
        char *to_print;

        // Si la chaîne est entourée de quotes simples, on ne fait PAS d’expansion
        size_t len = strlen(args[i]);
        if (len >= 2 && args[i][0] == '\'' && args[i][len - 1] == '\'')
        {
            // Affiche sans les quotes simples
            to_print = strndup(args[i] + 1, len - 2);
        }
        else
        {
            to_print = expand_variables(args[i], env);
        }

        if (to_print)
        {
            ft_putstr_fd(to_print, STDOUT_FILENO);
            free(to_print);
        }

        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }

    if (!n_option)
        ft_putchar_fd('\n', STDOUT_FILENO);

    return 0;
}








int builtin_cd(char **args, t_env *env)
{
    char *path;
    char old_pwd[1024];
    
    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)  //F
    {                                                            
        perror("cd: getcwd error");
        return (1);
    }
    if (!args[1] || ft_strcmp(args[1], "~") == 0) 
    {
        if (!env->home) 
        {
            ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
            return (1);
        }
        path = env->home;
    } 
    else 
        path = args[1];
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

int builtin_export(char **args, t_env *env)
{
    int i;
    char **envp_copy;
    char *equal_sign;

    i = 1;
    if (!args[1]) 
    {
        envp_copy = ft_arrdup(env->envp);
        if (!envp_copy)
            return (1);
        ft_sort_strarr(envp_copy);
        i = 0;
        while (envp_copy[i]) 
        {
            ft_putstr_fd("declare -x ", STDOUT_FILENO);
            equal_sign = ft_strchr(envp_copy[i], '=');
            if (equal_sign) 
            {
                write(STDOUT_FILENO, envp_copy[i], equal_sign - envp_copy[i]);
                ft_putstr_fd("=\"", STDOUT_FILENO);
                ft_putstr_fd(equal_sign + 1, STDOUT_FILENO);
                ft_putstr_fd("\"\n", STDOUT_FILENO);
            } 
            else 
            {
                ft_putstr_fd(envp_copy[i], STDOUT_FILENO);
                ft_putstr_fd("\n", STDOUT_FILENO);
            }
            i++;
        }
        ft_free_arr(envp_copy);
        return (0);
    }
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

void env_set(t_env *env, char *var)
{
    int i;
    char *name;
    char *equal_sign;
    char *existing_equal;
    size_t name_len;
    char **new_envp;
    int j;

    i = 0;
    equal_sign = ft_strchr(var, '=');
    if (equal_sign) 
        name = ft_substr(var, 0, equal_sign - var);
    else 
        name = ft_strdup(var);
    if (!name)
        return ;
    while (env->envp[i]) 
    {
        existing_equal = ft_strchr(env->envp[i], '=');
        if (existing_equal)
            name_len = existing_equal - env->envp[i];
        else
            name_len = ft_strlen(env->envp[i]);
        if (ft_strncmp(env->envp[i], name, name_len) == 0 && ft_strlen(name) == name_len) 
        {
            if (equal_sign) 
            {
                free(env->envp[i]);
                env->envp[i] = ft_strdup(var);
            }
            free(name);
            return ;
        }
        i++;
    }
    if (equal_sign || !env_get(env, name)) 
    {
        new_envp = malloc(sizeof(char *) * (i + 2));
        if (!new_envp) 
        {
            free(name);
            return ;
        }
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
    }
    if (ft_strcmp(name, "HOME") == 0 && equal_sign) 
    {
        free(env->home);
        env->home = ft_strdup(equal_sign + 1);
    }
    free(name);
}


void env_unset(t_env *env, const char *name)
{
    int i;
    int found;
    int name_len;
    char *equal_sign;
    int current_name_len;
    
    i = 0;
    found = -1;
    name_len = ft_strlen(name);
    while (env->envp[i]) 
    {
        equal_sign = ft_strchr(env->envp[i], '=');
        if (equal_sign) 
            current_name_len = equal_sign - env->envp[i];
        else
            current_name_len = ft_strlen(env->envp[i]);
        if (ft_strncmp(env->envp[i], name, name_len) == 0 && current_name_len == name_len) 
        {
            found = i;
            break;
        }
        i++;
    }
    if (found >= 0) 
    {
        free(env->envp[found]);
        while (env->envp[found + 1]) 
        {
            env->envp[found] = env->envp[found + 1];
            found++;
        }
        env->envp[found] = NULL;
        if (ft_strcmp(name, "HOME") == 0) 
        {
            free(env->home);
            env->home = NULL;
        }
    }
}

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

char **ft_arrdup(char **arr)
{
    int i;
    int len;
    char **dup;
    
    i = 0;
    len = 0;
    while (arr[len])
        len++;
    dup = malloc(sizeof(char *) * (len + 1));
    if (!dup)
        return (NULL);
    while (i < len) 
    {
        dup[i] = ft_strdup(arr[i]);
        if (!dup[i]) 
        {
            while (--i >= 0)
                free(dup[i]);
            free(dup);
            return (NULL);
        }
        i++;
    }
    dup[len] = NULL;
    return (dup);
}

void ft_free_arr(char **arr)
{
    int i;
    
    i = 0;
    if (!arr)
        return;
    
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void ft_sort_strarr(char **arr)
{
    int i;
    int j;
    char *temp;
    int len;
    
    len = 0;
    while (arr[len])
        len++;
    for (i = 0; i < len - 1; i++) 
    {
        for (j = 0; j < len - i - 1; j++) 
        {
            if (ft_strcmp(arr[j], arr[j + 1]) > 0) 
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
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

