#include "../../inc/executor.h"


void child_process(t_command *cmd, int **pipes, int i, t_env *env)
{
    int j;
    
    if (handle_infile(cmd) != 0)
        exit(1);
    if (handle_outfile(cmd) != 0)
        exit(1);
    if (i > 0)
        dup2(pipes[i - 1][0], STDIN_FILENO);
    if (cmd->next)
        dup2(pipes[i][1], STDOUT_FILENO);
    j = 0;
    while (pipes[j])
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (is_builtin(cmd))
        exit(execute_builtin(cmd, env));
    else
        execute_child_process(cmd, env);
}

void wait_and_cleanup(int **pipes, pid_t *pids, int n, t_env *env)
{
    int i;
    int status;
    
    i = 0;
    while (i < n)
    {
        waitpid(pids[i], &status, 0);
        if (i == n - 1)
        {
            if (WIFEXITED(status))
                env->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                env->exit_status = 128 + WTERMSIG(status);
        }
        i++;
    }
    cleanup_memory(pipes, pids, n);
}


void cleanup_memory(int **pipes, pid_t *pids, int n)
{
    int i;
    
    i = 0;
    while (i < n - 1)
    {
        free(pipes[i]);
        i++;
    }
    free(pipes);
    free(pids);
}

static void cleanup_failed_setup(int **pipes, pid_t *pids, int count)
{
    int i;
    
    i = 0;
    while (i < count)
    {
        if (pipes[i])
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
            free(pipes[i]);
        }
        i++;
    }
    free(pipes);
    free(pids);
}

int create_all_pipes(int **pipes, int num_cmds)
{
    int i;
    
    i = 0;
    while (i < num_cmds - 1)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i])
            return (-1);
        if (pipe(pipes[i]) < 0)
        {
            free(pipes[i]);
            return (-1);
        }
        i++;
    }
    pipes[i] = NULL;
    return (0);
}

int fork_all_processes(t_command *cmds, int **pipes, pid_t *pids, t_env *env)
{
    t_command *cur;
    int i;
    
    cur = cmds;
    i = 0;
    while (cur)
    {
        pids[i] = fork();
        if (pids[i] == 0)
            child_process(cur, pipes, i, env);
        if (pids[i] < 0)
            return (-1);
        cur = cur->next;
        i++;
    }
    return (0);
}

void close_all_pipes_parent(int **pipes)
{
    int i;
    
    i = 0;
    while (pipes[i])
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

void execute_pipeline(t_command *cmds, t_env *env)
{
    int num_cmds;
    int **pipes;
    pid_t *pids;
    
    num_cmds = count_cmds(cmds);
    if (num_cmds == 1)
        return (execute_command(cmds, env));
    pipes = malloc(sizeof(int *) * num_cmds);
    pids = malloc(sizeof(pid_t) * num_cmds);
    if (!pipes || !pids)
        return (free(pipes), free(pids));
    if (create_all_pipes(pipes, num_cmds) < 0)
        return (cleanup_failed_setup(pipes, pids, num_cmds - 1));
    if (fork_all_processes(cmds, pipes, pids, env) < 0)
        return (cleanup_failed_setup(pipes, pids, num_cmds - 1));
    close_all_pipes_parent(pipes);
    wait_and_cleanup(pipes, pids, num_cmds, env);
}


void execute_all_commands(t_command *cmds, t_env *env)
{
    if (!cmds)
        return;
    execute_pipeline(cmds, env);
}