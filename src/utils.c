/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 23:13:01 by iayni             #+#    #+#             */
/*   Updated: 2022/06/18 15:40:28 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void    dst_mutex(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->var->num_philo)
        pthread_mutex_destroy(&philo->fork[i++]);
}

unsigned long   in_time(void)
{
    struct timeval time;
    unsigned long l;
    unsigned long s;
    unsigned long u;
    
    gettimeofday(&time, NULL);
    s = (time.tv_sec * 1000);
    u = (time.tv_usec / 1000);
    l = s + u;
    return (l);
}

unsigned long real_time(t_philo *philo)
{
    return (in_time() - philo->var->time);
}