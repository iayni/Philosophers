/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:32:26 by iayni             #+#    #+#             */
/*   Updated: 2022/06/21 21:32:28 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

static void	*ft_bezero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n--)
		*str++ = '\0';
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*alloc;

	alloc = (void *)malloc(count * size);
	if (!alloc)
		return (NULL);
	ft_bezero(alloc, count * size);
	return (alloc);
}
