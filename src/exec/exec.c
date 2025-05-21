/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augeerae <augeerae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:21:21 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/21 13:11:36 by augeerae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        status = builtin_echo(cmd->args, env);
    else if (ft_strcmp(cmd->args[0], "env") == 0)
        status = builtin_env(env);
    else if (ft_strcmp(cmd->args[0], "export") == 0)
        status = builtin_export(cmd->args, env);
    else if (ft_strcmp(cmd->args[0], "unset") == 0)
        status = builtin_unset(cmd->args, env);
    env->exit_status = status;
    return (status);
}

void execute_command(t_command *cmd, t_env *env)
{
    pid_t pid;
    int status;
    int stdin_backup;
    int stdout_backup;

    status = 0;
    stdin_backup = -1;
    stdout_backup = -1;
    if (!cmd || !cmd->args || !cmd->args[0])
        return ;
    if (is_builtin(cmd) && (!cmd->next))
    {
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
    else
    {
        pid = fork();
        if (pid == 0)
        {
            status = handle_infile(cmd);
            if (status == 0)
                status = handle_outfile(cmd);   
            if (status == 0)
            {
                if (is_builtin(cmd))
                {
                    status = execute_builtin(cmd, env);
                    exit(status);
                }
                else
                {
                    execvp(cmd->args[0], cmd->args);
                    ft_putstr_fd(cmd->args[0], STDERR_FILENO);
                    ft_putstr_fd(": command not found\n", STDERR_FILENO);
                    exit(127);
                }
            }
            exit(1);
        }
        else if (pid > 0)
        {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                env->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                env->exit_status = 128 + WTERMSIG(status);
        }
        else
        {
            perror("fork");
            env->exit_status = 1;
        }
    }
}



int handle_infile(t_command *cmd)
{
    int fd;
    int status = 0;

    status = 0;
    if (cmd->infile)
    {
        fd = open(cmd->infile, O_RDONLY);
        if (fd < 0)
        {
            perror(cmd->infile);
            status = -1;
        }
        else
        {
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
    }
    return status;
}

int handle_outfile(t_command *cmd)
{
    int fd;
    int flags;
    int status;

    status = 0;
    if (cmd->outfile)
    {
        flags = O_WRONLY | O_CREAT;
        flags |= (cmd->append ? O_APPEND : O_TRUNC);
        fd = open(cmd->outfile, flags, 0644);
        if (fd < 0)
        {
            perror(cmd->outfile);
            status = -1;
        }
        else
        {
            dup2(fd, STDOUT_FILENO);  // Redirection de la sortie
            close(fd);
        }
    }
    return (status);
}

void execute_pipeline(t_command *cmds, t_env *env)
{
    int num_cmds = 0;
    t_command *current = cmds;
    int **pipes = NULL;
    pid_t *pids = NULL;
    int i, status;
    
    
    while (current) 
    {
        num_cmds++;
        current = current->next;
    }
    if (num_cmds == 1) 
    {
        execute_command(cmds, env);
        return ;
    }
    pipes = malloc(sizeof(int *) * (num_cmds - 1));
    if (!pipes) 
    {
        perror("malloc");
        return ;
    }
    for (i = 0; i < num_cmds - 1; i++) 
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i]) 
        {
            perror("malloc");
            goto cleanup;
        }
        if (pipe(pipes[i]) < 0) 
        {
            perror("pipe");
            goto cleanup;
        }
    }
    pids = malloc(sizeof(pid_t) * num_cmds);
    if (!pids) 
    {
        perror("malloc");
        goto cleanup;
    }
    current = cmds;
    for (i = 0; i < num_cmds; i++) 
    {
        pids[i] = fork();
        if (pids[i] < 0) 
        {
            perror("fork");
            goto cleanup;
        }
        else if (pids[i] == 0) 
        {
            
            if (i > 0)
                dup2(pipes[i - 1][0], STDIN_FILENO);
            if (i < num_cmds - 1) 
                dup2(pipes[i][1], STDOUT_FILENO);
            for (int j = 0; j < num_cmds - 1; j++) 
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            status = handle_infile(current);
            if (status == 0)
                status = handle_outfile(current);
            if (status == 0) 
            {
                if (is_builtin(current)) 
                {
                    status = execute_builtin(current, env);
                    exit(status);
                } else 
                {
                    execvp(current->args[0], current->args);
                    ft_putstr_fd(current->args[0], STDERR_FILENO);
                    ft_putstr_fd(": command not found\n", STDERR_FILENO);
                    exit(127);
                }
            }
            exit(1);
        }
        current = current->next;
    }
    for (i = 0; i < num_cmds - 1; i++) 
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    for (i = 0; i < num_cmds; i++) 
    {
        waitpid(pids[i], &status, 0);
        if (i == num_cmds - 1) 
        { 
            if (WIFEXITED(status))
                env->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                env->exit_status = 128 + WTERMSIG(status);
        }
    }
cleanup:
    if (pipes) 
    {
        for (i = 0; i < num_cmds - 1 && pipes[i]; i++)
            free(pipes[i]);
        free(pipes);
    }
    if (pids)
        free(pids);
}

void execute_all_commands(t_command *cmds, t_env *env)
{
    if (!cmds)
        return;
    execute_pipeline(cmds, env);
}

void sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void setup_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

































// // === BUILTINS ===

// int is_builtin(t_command *cmd)
// {
//     int result;

//     result = 0;
//     if (cmd->args && cmd->args[0])
//     {
//         if (strcmp(cmd->args[0], "cd") == 0)
//             result = 1;
//         else if (strcmp(cmd->args[0], "exit") == 0)
//             result = 1;
//         else if (strcmp(cmd->args[0], "pwd") == 0)
//             result = 1;
//         else if (strcmp(cmd->args[0], "echo") == 0)
//             result = 1;
//         else if (strcmp(cmd->args[0], "env") == 0)
//             result = 1;
//         else if 
//             result = 0;
//     }
//     return (result);
// }

// int execute_builtin(t_command *cmd)
// {
//     int status;

//     status = 0;
//     if (strcmp(cmd->args[0], "cd") == 0)
//     {
//         if (!cmd->args[1])
//         {
//             fprintf(stderr, "cd: missing argument\n");
//             status = 1;
//         }
//         else if (chdir(cmd->args[1]) != 0)
//         {
//             perror("cd");
//             status = 1;
//         }
//     }
//     else if (strcmp(cmd->args[0], "exit") == 0)
//     {
//         exit(0);
//     }
//     else if (strcmp(cmd->args[0], "pwd") == 0)
//     {
//         char cwd[1024];

//         if (getcwd(cwd, sizeof(cwd)))
//             printf("%s\n", cwd);
//         else
//             perror("pwd");
//     }
//     else if (strcmp(cmd->args[0], "echo") == 0)
//     {
//         int i;

//         i = 1;
//         while (cmd->args[i])
//         {
//             printf("%s", cmd->args[i]);
//             if (cmd->args[i + 1])
//                 printf(" ");
//             i++;
//         }
//         printf("\n");
//     }
//     else if (strcmp(cmd->args[0], "env") == 0)
//     {
//         extern char **environ;
//         int i;

//         i = 0;
//         while (environ[i])
//         {
//             printf("%s\n", environ[i]);
//             i++;
//         }
//     }
//     return (status);
// }

// // === REDIRECTIONS ===

// int handle_infile(t_command *cmd)
// {
//     int fd;
//     int status;

//     status = 0;
//     if (cmd->infile)
//     {
//         fd = open(cmd->infile, O_RDONLY);
//         if (fd < 0)
//         {
//             perror(cmd->infile);
//             status = -1;
//         }
//         else
//         {
//             dup2(fd, STDIN_FILENO);
//             close(fd);
//         }
//     }
//     return (status);
// }

// int handle_outfile(t_command *cmd)
// {
//     int fd;
//     int flags;
//     int status;

//     status = 0;
//     if (cmd->outfile)
//     {
//         flags = O_WRONLY | O_CREAT;
//         flags |= (cmd->append ? O_APPEND : O_TRUNC);
//         fd = open(cmd->outfile, flags, 0644);
//         if (fd < 0)
//         {
//             perror(cmd->outfile);
//             status = -1;
//         }
//         else
//         {
//             dup2(fd, STDOUT_FILENO);
//             close(fd);
//         }
//     }
//     return (status);
// }

// // === EXECUTION ===

// void execute_command(t_command *cmd)
// {
//     pid_t pid;
//     int status;

//     if (!cmd || !cmd->args || !cmd->args[0])
//         return;
    
//     status = 0;
//     if (is_builtin(cmd))
//     {
//         status = handle_infile(cmd);
//         if (status == 0)
//             status = handle_outfile(cmd);
//         if (status == 0)
//             status = execute_builtin(cmd);
//     }
//     else
//     {
//         pid = fork();
//         if (pid == 0)
//         {
//             // Child process
//             status = handle_infile(cmd);
//             if (status == 0)
//                 status = handle_outfile(cmd);
//             if (status == 0)
//             {
//                 execvp(cmd->args[0], cmd->args);
//                 perror("execvp");
//                 exit(1);
//             }
//         }
//         else if (pid > 0)
//         {
//             // Parent process
//             waitpid(pid, &status, 0);
//         }
//         else
//         {
//             perror("fork");
//         }
//     }
// }

// void execute_all_commands(t_command *cmds)
// {
//     t_command *current;
//     int status;

//     current = cmds;
//     status = 0;
//     while (current)
//     {
//         execute_command(current);
//         current = current->next;
//     }
// }


