/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:45:33 by iayni             #+#    #+#             */
/*   Updated: 2022/06/24 21:45:33 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	print(t_philo *philo, char *str, int n)
{
	pthread_mutex_lock(&philo->data->print);
	if (str)
		printf("%lldms %d %s\n", (get_time() - philo->data->time),
			philo->id, str);
	if (n)
		pthread_mutex_unlock(&philo->data->print);
}
