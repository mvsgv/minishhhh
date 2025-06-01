#include "../../inc/executor.h"

int is_builtin(t_command *cmd)
{
    if (cmd->args && cmd->args[0])
    {
        if (ft_strcmp(cmd->args[0], "cd") == 0)
            return (1);
        else if (ft_strcmp(cmd->args[0], "exit") == 0)
            return (1);
        else if (ft_strcmp(cmd->args[0], "pwd") == 0)
            return (1);
        else if (ft_strcmp(cmd->args[0], "echo") == 0)
            return (1);
        else if (ft_strcmp(cmd->args[0], "env") == 0)
            return (1);
        else if (ft_strcmp(cmd->args[0], "export") == 0)
            return (1);
        else if (ft_strcmp(cmd->args[0], "unset") == 0)
            return (1);
    }
    return (0);
}

int execute_builtin(t_command *cmd, t_env *env)
{
    int status;
    
    status = 0;
    if (ft_strcmp(cmd->args[0], "cd") == 0)
        status = builtin_cd(cmd->args, env);
    else if (ft_strcmp(cmd->args[0], "exit") == 0)
        status = builtin_exit(cmd->args);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        status = builtin_pwd(env);
    else if (ft_strcmp(cmd->args[0], "echo") == 0)
        status = builtin_echo(cmd->args);
    else if (ft_strcmp(cmd->args[0], "env") == 0)
        status = builtin_env(env);
    else if (ft_strcmp(cmd->args[0], "export") == 0)
        status = builtin_export(cmd->args, env);
    else if (ft_strcmp(cmd->args[0], "unset") == 0)
        status = builtin_unset(cmd->args, env);
    env->exit_status = status;
    return (status);
}

static void execute_builtin_no_fork(t_command *cmd, t_env *env)   /////EXIT
{
    int status;
    int stdin_backup;
    int stdout_backup;

    stdin_backup = dup(STDIN_FILENO);
    stdout_backup = dup(STDOUT_FILENO);
    status = handle_infile(cmd);
    if (status == 0)
        status = handle_outfile(cmd);
    if (status == 0)
        status = execute_builtin(cmd, env);
    if (stdin_backup >= 0)
    {
        dup2(stdin_backup, STDIN_FILENO);
        close(stdin_backup);
    }
    if (stdout_backup >= 0)
    {
        dup2(stdout_backup, STDOUT_FILENO);
        close(stdout_backup);
    }
    env->exit_status = status;
}

void free_split(char **tab)
{
    int i;

    if (!tab)
        return;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

static void copy_str(char *dest, const char *src, int *i)
{
    int j;

    j = 0;
    while (src[j])
    {
        dest[*i] = src[j];
        (*i)++;
        j++;
    }
}

char *path_join(const char *dir, const char *file)
{
    char *full_path;
    int len_dir;
    int len_file;
    int i;

    len_dir = 0;
    len_file = 0;
    while (dir[len_dir])
        len_dir++;
    while (file[len_file])
        len_file++;
    full_path = malloc(len_dir + len_file + 2);
    if (!full_path)
    {
        perror("malloc");
        return (NULL);
    }
    i = 0;
    copy_str(full_path, dir, &i);
    if (i > 0 && full_path[i - 1] != '/')
        full_path[i++] = '/';
    copy_str(full_path, file, &i);
    full_path[i] = '\0';
    return (full_path);
}

static char *search_in_paths(char **paths, char *cmd)
{
    char *full_path;
    int i;

    i = 0;
    while (paths[i])
    {
        full_path = path_join(paths[i], cmd);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}

char *get_command_path(char *cmd, t_env *env)   ////!!!!!!
{
    char *path_env;
    char **paths;
    char *result;

    if (ft_strchr(cmd, '/'))
        return (ft_strdup(cmd));
    path_env = env_get(env, "PATH");
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    result = search_in_paths(paths, cmd);
    free_split(paths);
    return (result);
}

void execute_child_process(t_command *cmd, t_env *env)
{
    char *cmd_path;
    
    if (handle_infile(cmd) != 0)
        exit(1);
    if (handle_outfile(cmd) != 0)
        exit(1);
    if (is_builtin(cmd))
        exit(execute_builtin(cmd, env));
    cmd_path = get_command_path(cmd->args[0], env);
    if (!cmd_path)
    {
        ft_putstr_fd(cmd->args[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        exit(127);
    }
    execve(cmd_path, cmd->args, env->envp);
    perror("execve");
    free(cmd_path);
    exit(1);
}

void execute_command(t_command *cmd, t_env *env)
{
    pid_t pid;
    int status;

    if (!cmd || !cmd->args || !cmd->args[0])
        return ;
    if (!cmd->args[0] || cmd->args[0][0] == '\0')
    {
	    env->exit_status = 127;
	    return ;
    }
    if (is_builtin(cmd) && (!cmd->next))
        return execute_builtin_no_fork(cmd, env);
    pid = fork();
    if (pid == 0)
        execute_child_process(cmd, env);
    if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            env->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            env->exit_status = 128 + WTERMSIG(status);
    }
    if (pid < 0)
    {
        perror("fork");
        env->exit_status = 1;
    }
}
