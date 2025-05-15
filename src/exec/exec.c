#include "../../inc/executor.h"


// === BUILTINS ===

int is_builtin(t_command *cmd)
{
    if (cmd->args && cmd->args[0])
    {
        // Vérification des commandes internes (builtins)
        if (strcmp(cmd->args[0], "cd") == 0)
            return 1;
        else if (strcmp(cmd->args[0], "exit") == 0)
            return 1;
        else if (strcmp(cmd->args[0], "pwd") == 0)
            return 1;
        else if (strcmp(cmd->args[0], "echo") == 0)
            return 1;
        else if (strcmp(cmd->args[0], "env") == 0)
            return 1;
    }
    return 0;
}

int execute_builtin(t_command *cmd)
{
    int status = 0;

    // Traitement des commandes internes
    if (strcmp(cmd->args[0], "cd") == 0)
    {
        if (!cmd->args[1])
        {
            fprintf(stderr, "cd: missing argument\n");
            status = 1;
        }
        else if (chdir(cmd->args[1]) != 0)
        {
            perror("cd");
            status = 1;
        }
    }
    else if (strcmp(cmd->args[0], "exit") == 0)
        exit(0);
    else if (strcmp(cmd->args[0], "pwd") == 0)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)))
            printf("%s\n", cwd);
        else
            perror("pwd");
    }
    else if (strcmp(cmd->args[0], "echo") == 0)
    {
        int i = 1;
        // Vérification de l'option -n pour echo
        while (cmd->args[i])
        {
            printf("%s", cmd->args[i]);
            if (cmd->args[i + 1])
                printf(" ");
            i++;
        }
        printf("\n");
    }
    else if (strcmp(cmd->args[0], "env") == 0)
    {
        extern char **environ;
        int i = 0;
        while (environ[i])
        {
            printf("%s\n", environ[i]);
            i++;
        }
    }
    return status;
}

// === REDIRECTIONS ===

int handle_infile(t_command *cmd)
{
    int fd;
    int status = 0;

    // Si un fichier d'entrée est spécifié
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
            dup2(fd, STDIN_FILENO);  // Redirection de l'entrée
            close(fd);
        }
    }
    return status;
}

int handle_outfile(t_command *cmd)
{
    int fd;
    int flags;
    int status = 0;

    // Si un fichier de sortie est spécifié
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
    return status;
}

// === EXECUTION ===

void execute_command(t_command *cmd)
{
    pid_t pid;
    int status = 0;

    if (!cmd || !cmd->args || !cmd->args[0])
        return;

    // Si la commande est un built-in, on gère les redirections manuellement
    if (is_builtin(cmd))
    {
        status = handle_infile(cmd);
        if (status == 0)
            status = handle_outfile(cmd);
        if (status == 0)
            status = execute_builtin(cmd);
    }
    else
    {
        pid = fork();
        if (pid == 0)
        {
            // Processus enfant pour exécuter une commande externe
            status = handle_infile(cmd);
            if (status == 0)
                status = handle_outfile(cmd);
            if (status == 0)
            {
                execvp(cmd->args[0], cmd->args);
                perror("execvp");
                exit(1);
            }
        }
        else if (pid > 0)
        {
            // Processus parent attend le retour du processus enfant
            waitpid(pid, &status, 0);
        }
        else
        {
            perror("fork");
        }
    }
}

void execute_all_commands(t_command *cmds)
{
    t_command *current = cmds;

    while (current)
    {
        execute_command(current);
        current = current->next;
    }
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


