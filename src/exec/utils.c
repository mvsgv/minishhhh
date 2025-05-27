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

static int open_outfile(const char *filename, int append)
{
    int flags;

    flags = O_WRONLY | O_CREAT;
    if (append)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    return open(filename, flags, 0644);
}

int handle_outfile(t_command *cmd)
{
    int fd;
    int status;

    status = 0;
    if (cmd->outfile)
    {
        fd = open_outfile(cmd->outfile, cmd->append);
        if (fd < 0)
        {
            perror(cmd->outfile);
            return (-1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            close(fd);
            return (-1);
        }
        close(fd);
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
