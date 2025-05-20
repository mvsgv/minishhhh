#include "../../inc/Minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/*int	main()
{
	printf("%d", ft_isdigit('l'));
}*/