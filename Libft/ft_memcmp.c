/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:32:50 by mavissar          #+#    #+#             */
/*   Updated: 2024/04/12 12:50:19 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*l;
	unsigned char	*m;

	l = (void *)s1;
	m = (void *)s2;
	i = 0;
	while (i < n)
	{
		if (l[i] != m[i])
			return (l[i] - m[i]);
		i++;
	}
	return (0);
}
/*int	main()
{
	printf("%d\n", ft_memcmp("almost", "bb", 8));
	printf("%d\n", memcmp("almost", "bb", 8));
}*/