/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:45:45 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/05 17:31:39 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

//┌──────┐  ┌───────┐  ┌────┐  ┌──────┐  ┌─────┐  ┌───────┐  ┌─────────┐
//│"echo"│->│"hello"│->│ "|"│->│"grep"│->│"foo"│->│  ">"  │->│"out.txt"│
//│WORD  │  │WORD   │  │PIPE│  │WORD  │  │WORD │  │RED_OUT│  │ WORD    │
//└──────┘  └───────┘  └────┘  └──────┘  └─────┘  └───────┘  └─────────┘
/*Chaque bloc a trois parties :
- value → la chaîne de caractères du token (ex: "echo")
- type → le type du token (ex: WORD, PIPE, RED_OUT)
- next → un pointeur vers le prochain token*/

/*Retourne le type de token correspondant a la chaine,
si ce n est pas un operateur connu on le considere comme WORD*/
/*
GET_ENV_VALUE - Retrieve the value of an environment variable by its name.
envp[0] = "PATH=/usr/bin:/bin"
envp[1] = "USER=mavissar"
envp[2] = "HOME=/Users/mavissar"
So each entry is a string of the form "KEY=VALUE"
If env->envp[i] = "USER=mavissar":
ft_strncmp("USER=mavissar", "USER", 4) → ✅ matches
env->envp[i][4] == '=' → ✅
We return env->envp[i] + 5 → "mavissar"
*/

/* CREATE_TOKEN - Create a new token with the given value and type.
Allocates memory for the token and its value.
Returns a pointer to the newly created token, or NULL on failure.
Cree un nouveau token avec la valeur et le type.
Alloue dynamiquement la memoire pour le token et sa valeur*/

/* ADD_TOKEN - Add a new token to the end of the linked list.
	Si la liste est vide, le token devient le premier element.
	Traverse la liste jusqu'au dernier token et ajoute le nouveau token a la fin.
	Si la liste est vide,le nouveau token devient le premier element de la liste.
*/
t_token_type	get_token_type(const char *s)
{
	if (ft_strncmp(s, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(s, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(s, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(s, "<", 1) == 0)
		return (RED_IN);
	if (ft_strncmp(s, ">", 1) == 0)
		return (RED_OUT);
	return (WORD);
}

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **list, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = create_token(value, type);
	if (!new)
		return ;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_tok(t_token *list)
{
	t_token	*next;

	while (list)
	{
		next = list->next;
		free(list->value);
		free(list);
		list = next;
	}
}

char	*get_env_value(char *name, t_env *env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], name, len) == 0
			&& env->envp[i][len] == '=')
			return (env->envp[i] + len + 1);
		i++;
	}
	return ("");
}
