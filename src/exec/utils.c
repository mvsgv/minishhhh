#include "../../inc/executor.h"

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

void copy_str(char *dest, const char *src, int *i)
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











