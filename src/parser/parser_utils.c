/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:22:50 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/04 20:09:01 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

/*cette fonction sert a construire dynaiquement les arguments.
Parce que tu ne connais pas à l'avance combien d'arguments la commande aura

grep -i "error" log.txt | wc -l

Tu veux découper ça en deux commandes :

	grep -i "error" log.txt
	→ doit devenir : args = {"grep", "-i", "error", "log.txt", NULL}

	wc -l
	→ devient : args = {"wc", "-l", NULL}*/
/*add_arg
if (*args)
		while ((*args)[len]) //compter le nombre d elements existans dans args
		new_args = malloc(sizeof(char *) * (len + 2)); // allouer un nv tab
	while (++i < len) //recopier les ancien pointeurs vers le nv tab
		new_args[i] = (*args)[i]; // on copie les pointeurs pas le contenu
	new_args[len] = ft_strdup(word);
			// ici je rajoute le nv mot (je ree une chaine avec strdup)
	free(*args); // liberer l ancien tab de pointeur
	*args = new_args;// redirection de args vers le nv tableau
Add_arg
temp = *list;//premiere cmd dans la liste
	while (temp->next) //on avance sur la derniere
		temp = temp->next;
	temp->next = cmd;//on rajoute la cmd a la fin de la liste
	*/
void	add_arg(char ***args, char *word)
{
	int		i;
	int		len;
	char	**new_args;

	i = -1;
	len = 0;
	if (*args)
		while ((*args)[len])
			len++;
	new_args = malloc(sizeof(char *) * (len + 2));
	if (!new_args)
		return ;
	while (++i < len)
		new_args[i] = (*args)[i];
	new_args[len] = ft_strdup(word);
	new_args[len + 1] = NULL;
	free(*args);
	*args = new_args;
}

void	free_cmds(t_command *cmd)
{
	t_command	*next;
	int			i;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
		cmd = next;
	}
}

void	add_cmd(t_command **list, t_command *cmd)
{
	t_command	*temp;

	if (!*list)
	{
		*list = cmd;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = cmd;
}

t_command	*parse_error(t_command *cmd_lst, t_command *current, char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putendl_fd(msg, 2);
	free(cmd_lst);
	free(current);
	return (NULL);
}
