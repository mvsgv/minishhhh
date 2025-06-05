/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:17 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/05 17:34:05 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

/*Systeme de tri : Tokenization/Lexer
Transforme une entree d'utilisateur et les structures en tokens
ex: echo "hello" | grep hello > file.txt
valeur : echo , type = WORD
valeur : | , type = PIPE
vaeur : > | type = RED_OUT
Il est important de faire la partie lexer avant la partie parser car le parser
attend une liste de tokens et non une string
Le parser lui construit une structure de commande (liste chainee de commandes)
et assigne les redirection, arguments, etc. Mais pour y arriver il aura besoin
de connaitre au minimum le nom des commandes, ce qu'est une argument ainsi
qu'un operateur. Si je n'ai pas de lexer, mon parser n'aura pas de syntax.


INPUT : echo "$HOME"
Lexer turns input into tokens ($USER becomes one token)
	lexer creates { value: "$HOME", type: WORD }
Expander replaces values inside tokens
	expander turns into { value: "/home/mavissar", type: WORD }
Parser builds the command tree using final values
	parser sees command: echo
				args: ["/home/mavissar"]

If you expand before lexing, you'd break quotes/syntax.
If you expand after parsing, it's too late (parser might make wrong structure).

Lexer			Breaks raw input into tokens (echo, >, etc.)
Expander	Replaces $VAR, $?, inside tokens
Parser  	Builds the command list (structure, pipes)

Handle_Quote
quote = line[*i];
	start = *i;
	(*i)++; -> skip opening quote
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++; -> skip closing quote include the quotes in the token
	word = ft_substr(line, start, *i - start);
	add_token(list, word, WORD);
	free(word);*/

void	handle_word(const char *line, int *i, t_token **list)
{
	int		start;
	char	*word;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|'
		&& line[*i] != '<' && line[*i] != '>')
		(*i)++;
	word = ft_substr(line, start, *i - start);
	add_token(list, word, WORD);
	free(word);
}

void	handle_operator(const char *line, int *i, t_token **list)
{
	int		start;
	char	*operator;

	start = *i;
	if (line[*i] && line[*i + 1] && line[*i] == line[*i + 1])
		(*i)++;
	(*i)++;
	operator = ft_substr(line, start, *i - start);
	add_token(list, operator, get_token_type(operator));
	free(operator);
}

static int	process_quote_char(char c, int *in_sq, int *in_dq)
{
	if (c == '\'' && !*in_dq)
	{
		*in_sq = !*in_sq;
		return (1);
	}
	if (c == '"' && !*in_sq)
	{
		*in_dq = !*in_dq;
		return (1);
	}
	return (0);
}

char	*remove_quotes(const char *str)
{
	char	*res;
	int		j;
	int		in_sq;
	int		in_dq;
	int		i;

	i = -1;
	in_sq = 0;
	in_dq = 0;
	j = 0;
	res = ft_calloc(ft_strlen(str) + 1, 1);
	if (!res)
		return (NULL);
	while (str[++i])
	{
		if (process_quote_char(str[i], &in_sq, &in_dq))
			continue ;
		res[j++] = str[i];
	}
	return (res);
}
