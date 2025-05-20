#include "../../inc/builtins.h"

// echo command with -n option
int builtin_echo(char **args)
{
    int i = 1;
    int n_option = 0;
    
    // Check for -n option
    if (args[1] && ft_strcmp(args[1], "-n") == 0) {
        n_option = 1;
        i = 2;
    }
    // Print arguments
    while (args[i]) {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    // Print newline if -n is not specified
    if (!n_option)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return 0;
}

// cd command with relative or absolute path
int builtin_cd(char **args, t_env *env)
{
    char *path;
    char old_pwd[1024];
    
    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL) {                                                             //F
        perror("cd: getcwd error");
        return 1;
    }
    // If no argument is provided, go to HOME directory
    if (!args[1] || ft_strcmp(args[1], "~") == 0) {
        if (!env->home) {
            ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
            return 1;
        }
        path = env->home;
    } else {
        path = args[1];
    }
    // Change directory
    if (chdir(path) != 0) {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        perror(path);
        return 1;
    }
    return 0;
}

// pwd command
int builtin_pwd(void)
{
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) == NULL) {                                                                              //F
        perror("pwd");
        return 1;
    }
    ft_putstr_fd(cwd, STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
    
    return 0;
}


int builtin_exit(char **args)
{
    int exit_code = 0;
    
    if (args[1]) {
        // Check if the argument is a valid number
        int i = 0;
        while (args[1][i]) {
            if (!ft_isdigit(args[1][i])) {
                ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
                exit(255);
            }
            i++;
        }
        // Convert the argument to an integer
        exit_code = ft_atoi(args[1]);
        // Check if there are too many arguments
        if (args[2]) {
            ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
            return 1;
        }
    }
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    exit(exit_code);
}

int builtin_export(char **args, t_env *env)
{
    int i = 1;
    
    // If no arguments, print the environment variables in a sorted, export-like format
    if (!args[1]) {
        // Create a copy of the environment variables array
        char **envp_copy = ft_arrdup(env->envp);
        if (!envp_copy)
            return 1;
            
        // Sort the array
        ft_sort_strarr(envp_copy);
        
        // Print in export format
        i = 0;
        while (envp_copy[i]) {
            ft_putstr_fd("declare -x ", STDOUT_FILENO);
            
            // Find the equal sign
            char *equal_sign = ft_strchr(envp_copy[i], '=');
            if (equal_sign) {
                // Print variable name
                write(STDOUT_FILENO, envp_copy[i], equal_sign - envp_copy[i]);
                
                // Print equal sign and quoted value
                ft_putstr_fd("=\"", STDOUT_FILENO);
                ft_putstr_fd(equal_sign + 1, STDOUT_FILENO);
                ft_putstr_fd("\"\n", STDOUT_FILENO);
            } else {
                // Print variable without value
                ft_putstr_fd(envp_copy[i], STDOUT_FILENO);
                ft_putstr_fd("\n", STDOUT_FILENO);
            }
            i++;
        }
        
        // Free the copy
        ft_free_arr(envp_copy);
        return 0;
    }
    // Process arguments (variable assignments)
    while (args[i]) {
        // Check if the variable name is valid
        if (!is_valid_identifier(args[i])) {
            ft_putstr_fd("export: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            i++;
            continue;
        }
        
        // Add or update the variable in the environment
        env_set(env, args[i]);
        i++;
    }
    return 0;
}

// unset command
int builtin_unset(char **args, t_env *env)
{
    int i = 1;
    
    while (args[i]) {
        // Check if the variable name is valid
        if (!is_valid_identifier(args[i])) {
            ft_putstr_fd("unset: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            i++;
            continue;
        }
        
        // Remove the variable from the environment
        env_unset(env, args[i]);
        i++;
    }
    return 0;
}



// env command
int builtin_env(t_env *env)
{
    int i = 0;
    
    while (env->envp[i]) {
        ft_putstr_fd(env->envp[i], STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        i++;
    }
    
    return 0;
}


//ENV

// Set an environment variable
void env_set(t_env *env, char *var)
{
    int i = 0;
    char *name;
    char *equal_sign;
    
    // Find the equal sign
    equal_sign = ft_strchr(var, '=');
    
    // Extract the variable name
    if (equal_sign) {
        name = ft_substr(var, 0, equal_sign - var);
    } else {
        name = ft_strdup(var);
    }
    
    if (!name)
        return;
    
    // Check if the variable already exists
    while (env->envp[i]) {
        // Extract the name of the existing variable
        char *existing_equal = ft_strchr(env->envp[i], '=');
        size_t name_len;
        
        if (existing_equal) {
            name_len = existing_equal - env->envp[i];
        } else {
            name_len = ft_strlen(env->envp[i]);
        }
        
        // Compare the names
        if (ft_strncmp(env->envp[i], name, name_len) == 0 && ft_strlen(name) == name_len) {
            // Variable exists, update it if we have a value
            if (equal_sign) {
                free(env->envp[i]);
                env->envp[i] = ft_strdup(var);
            }
            free(name);
            return;
        }
        i++;
    }
    
    // Variable doesn't exist, add it if it has a value or it's a new variable without a value
    if (equal_sign || !env_get(env, name)) {
        char **new_envp = malloc(sizeof(char *) * (i + 2));
        if (!new_envp) {
            free(name);
            return;
        }
        
        // Copy existing variables
        int j = 0;
        while (j < i) {
            new_envp[j] = env->envp[j];
            j++;
        }
        
        // Add the new variable
        new_envp[i] = equal_sign ? ft_strdup(var) : ft_strdup(name);
        new_envp[i + 1] = NULL;
        
        // Free the old array (but not its contents)
        free(env->envp);
        env->envp = new_envp;
    }
    
    // Update HOME if necessary
    if (ft_strcmp(name, "HOME") == 0 && equal_sign) {
        free(env->home);
        env->home = ft_strdup(equal_sign + 1);
    }
    
    free(name);
}


void env_unset(t_env *env, const char *name)
{
    int i = 0;
    int found = -1;
    int name_len = ft_strlen(name);
    
    // Find the variable
    while (env->envp[i]) {
        char *equal_sign = ft_strchr(env->envp[i], '=');
        int current_name_len;
        
        if (equal_sign) {
            current_name_len = equal_sign - env->envp[i];
        } else {
            current_name_len = ft_strlen(env->envp[i]);
        }
        
        // Compare the names
        if (ft_strncmp(env->envp[i], name, name_len) == 0 && current_name_len == name_len) {
            found = i;
            break;
        }
        i++;
    }
    // If found, remove it
    if (found >= 0) {
        // Free the variable
        free(env->envp[found]);
        
        // Shift all variables after this one
        while (env->envp[found + 1]) {
            env->envp[found] = env->envp[found + 1];
            found++;
        }
        
        // Set the last pointer to NULL
        env->envp[found] = NULL;
        
        // If it was HOME, clear the cached value
        if (ft_strcmp(name, "HOME") == 0) {
            free(env->home);
            env->home = NULL;
        }
    }
}


// Get an environment variable
char *env_get(t_env *env, const char *name)
{
    int i = 0;
    int name_len = ft_strlen(name);
    
    while (env->envp[i]) {
        // Check if this variable starts with the name followed by '='
        if (ft_strncmp(env->envp[i], name, name_len) == 0 && env->envp[i][name_len] == '=') {
            return env->envp[i] + name_len + 1;
        }
        i++;
    }
    
    return NULL;
}


t_env *env_init(char **envp)
{
    t_env *env;
    
    env = malloc(sizeof(t_env));
    if (!env)
        return NULL;
    
    // Duplicate the environment variables array
    env->envp = ft_arrdup(envp);
    if (!env->envp) {
        free(env);
        return NULL;
    }
    
    // Set the initial exit status
    env->exit_status = 0;
    
    // Cache the HOME variable
    env->home = env_get(env, "HOME");
    if (env->home)
        env->home = ft_strdup(env->home);
    
    return env;
}

// Free the environment
void env_free(t_env *env)
{
    if (!env)
        return;
    
    if (env->envp)
        ft_free_arr(env->envp);
    
    if (env->home)
        free(env->home);
    
    free(env);
}




char **ft_arrdup(char **arr)
{
    int i = 0;
    int len = 0;
    char **dup;
    
    // Count the array length
    while (arr[len])
        len++;
    
    // Allocate memory for the new array
    dup = malloc(sizeof(char *) * (len + 1));
    if (!dup)
        return NULL;
    
    // Copy the strings
    while (i < len) {
        dup[i] = ft_strdup(arr[i]);
        if (!dup[i]) {
            // Free already allocated strings in case of error
            while (--i >= 0)
                free(dup[i]);
            free(dup);
            return NULL;
        }
        i++;
    }
    dup[len] = NULL;
    
    return dup;
}

void ft_free_arr(char **arr)
{
    int i = 0;
    
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
    int len = 0;
    
    // Count the array length
    while (arr[len])
        len++;
    
    // Bubble sort
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - i - 1; j++) {
            if (ft_strcmp(arr[j], arr[j + 1]) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Check if a string is a valid identifier
bool is_valid_identifier(const char *str)
{
    int i = 0;
    
    // First character must be alphabetic or underscore
    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return false;
    
    // Remaining characters must be alphanumeric or underscore
    i = 1;
    while (str[i] && str[i] != '=') {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return false;
        i++;
    }
    
    return true;
}

