/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:05:10 by mavissar          #+#    #+#             */
/*   Updated: 2024/04/12 11:09:25 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == (char) c)
			return ((char *) s + i);
		i--;
	}
	if (s[i] == (char) c)
		return ((char *) s + i);
	return (NULL);
}
/*int		main()
{
	char	s[] = "ouf that was cold";
	int	c = 'w'; 
	printf("%s", ft_strrchr(s, c));
	printf("%s", strrchr(s, c));
}*/