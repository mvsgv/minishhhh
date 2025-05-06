/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:50:40 by mavissar          #+#    #+#             */
/*   Updated: 2024/05/07 18:36:41 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!find[i])
		return ((char *)str);
	while (i < len && str[i])
	{
		while (str[i + j] == find[j] && str[i + j] != '\0' && i + j < len
			&& find[j])
			j++;
		if (find[j] == '\0')
			return ((char *)&str[i]);
		i++;
		j = 0;
	}
	return (0);
}
