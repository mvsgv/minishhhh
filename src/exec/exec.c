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
        status = builtin_pwd();
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

static void execute_builtin_no_fork(t_command *cmd, t_env *env)
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
static void execute_child_process(t_command *cmd, t_env *env)
{
    int status;

    status = handle_infile(cmd);
    if (status == 0)
        status = handle_outfile(cmd);
    if (status != 0)
        exit(1);
    if (is_builtin(cmd))
    {
        status = execute_builtin(cmd, env);
        exit(status);
    }
    execvp(cmd->args[0], cmd->args);
    ft_putstr_fd(cmd->args[0], STDERR_FILENO);
    ft_putstr_fd(": command not found\n", STDERR_FILENO);
    exit(127);
}

void execute_command(t_command *cmd, t_env *env)
{
    pid_t pid;
    int status;

    if (!cmd || !cmd->args || !cmd->args[0])
        return ;
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