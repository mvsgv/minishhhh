/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:35:25 by mavissar          #+#    #+#             */
/*   Updated: 2024/05/07 17:15:36 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The ft_strmapi function creates a new string by applying 
//the specified function to each character of the input string.
// It first determines the length of the input string using the str_len helper 
//function. Memory is allocated to store the resulting string, 
//including space for the null.
// If memory allocation fails, NULL is returned. 
// Then, the function iterates over each character of the input string,
// passing the current index and character to the provided function.
// The function returns a new character based on the index and input character,
// which is stored in the resulting string. 
//Finally, the null-terminator is appended,
// and the resulting string is returned.

#include "libft.h"

static char	*new_str(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	ft_bzero(str, n + 1);
	return (str);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = new_str(ft_strlen(s));
	if (!str)
		return (NULL);
	if (s && f)
	{
		while (s[i])
		{
			str[i] = f(i, s[i]);
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
