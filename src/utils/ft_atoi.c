#include "../../inc/Minishell.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	res = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		res = res * 10 + (str[i++] - 48);
	return (res * neg);
}
// int	main()
// {
// 	const char str[] ="  abc754";
// 	printf("%d\n", ft_atoi(((void *)0)));
// 	printf("%d\n", atoi(((void *)0)));
// }