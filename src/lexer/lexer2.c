/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:37:46 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/04 20:42:15 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static t_token	*merge_words(t_token *list)
{
	t_token	*cur;
	char	*joined;
	t_token	*to_free;

	cur = list;
	if (!cur)
		return (list);
	cur = cur->next;
	while (cur && cur->next)
	{
		if (cur->type == WORD && cur->next->type == WORD)
		{
			joined = ft_strjoin(cur->value, cur->next->value);
			free(cur->value);
			cur->value = joined;
			to_free = cur->next;
			cur->next = cur->next->next;
			free(to_free->value);
			free(to_free);
		}
		else
			cur = cur->next;
	}
	return (list);
}

static void	tokenize(const char *line, t_token **list)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '\'' || line[i] == '\"')
			handle_quote(line, &i, list);
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			handle_operator(line, &i, list);
		else
			handle_word(line, &i, list);
	}
}

static void	expand_tokens(t_token *list, t_env *env, int exit_code)
{
	char	*expanded;
	char	*final;

	while (list)
	{
		if (list->type == WORD)
		{
			expanded = expand_word(list->value, env, exit_code);
			final = remove_quotes(expanded);
			free(list->value);
			free(expanded);
			list->value = final;
		}
		list = list->next;
	}
}

t_token	*lexer(const char *line, t_env *env, int exit_code)
{
	t_token	*list;

	list = NULL;
	tokenize(line, &list);
	expand_tokens(list, env, exit_code);
	list = merge_words(list);
	return (list);
}
