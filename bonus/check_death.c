/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:56:55 by iayni             #+#    #+#             */
/*   Updated: 2022/06/26 20:56:55 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_eat(void *arg)
{
	t_data	*data;
	int		i;

	i = -1;
	data = (t_data *)arg;
	while (++i < data->num_philo)
	{
		sem_wait(data->twoforks);
		usleep(100);
	}
	sem_post(data->main);
	return (0);
}

void	*check_death(void *arg)
{
	t_philo			*philo;
	int				i;
	unsigned int	now;

	i = -1;
	philo = (t_philo *)arg;
	while (philo->data->finish == 0)
	{
		now = get_time();
		if (now >= philo->death_time)
		{
			philo->data->finish = 1;
			print(philo, " is dead");
			sem_wait(philo->eat);
			sem_post(philo->data->main);
			while (++i < philo->data->must_eat)
				sem_post(philo->data->twoforks);
		}
		usleep(100);
	}
	return (0);
}
