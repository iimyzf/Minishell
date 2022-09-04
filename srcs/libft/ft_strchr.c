#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*k;
	char	m;

	i = 0;
	m = c;
	k = (char *)s;
	while (*s)
	{
		if (*s == m)
			return (k + i);
		else
			i++;
		s++;
	}
	if (*s == c)
		return (k + i);
	return (0);
}