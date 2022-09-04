#include "libft.h"

void	*ft_calloc(int i, int s)
{
	char	*p;
	int		j;

	p = (char *)malloc(i * s);
	if (!p)
		return (NULL);
	j = 0;
	while (j < i * s)
	{
		p[j] = 0;
		j++;
	}
	return (p);
}