/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:35:12 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/26 20:03:10 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
/*int	main()
{
	char	s[] = "hello world";
	ft_bzero(s, 5);
	printf("%s\n", s);
}*/