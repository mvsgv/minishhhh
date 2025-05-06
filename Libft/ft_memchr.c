/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:18:14 by mavissar          #+#    #+#             */
/*   Updated: 2024/04/29 16:27:10 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s++ == (unsigned char) c)
			return ((void *)(unsigned char *)s -1);
	}
	return (NULL);
}
/*int	main()
{

	printf("%s", ft_memchr("she didnt see", 'i', 8));
	printf("%s", memchr("she didnt see", 'i', 8));
}*/