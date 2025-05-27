#include "../../inc/executor.h"

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
int count_cmds(t_command *cmds)
{
	int count = 0;

	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return count;
}