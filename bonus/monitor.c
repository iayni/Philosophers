/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:42:54 by iayni             #+#    #+#             */
/*   Updated: 2022/06/26 20:42:54 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_fork(t_philo *data)
{
	sem_wait(data->data->forks);
	print(data, "has taken a fork");
	sem_wait(data->data->forks);
	print(data, "has taken a fork");
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->eat);
	print(philo, " is eating");
	philo->death_time = get_time() + philo->data->time_to_die;
	philo->num_eat++;
	if (philo->data->must_eat > 0
		&& philo->num_eat == philo->data->must_eat)
		sem_post(philo->data->twoforks);
	sem_post(philo->eat);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static void	go_sleep(t_philo *philo)
{
	print(philo, "sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

static void	think(t_philo *philo)
{
	print(philo, "thinking");
}

void	monitor(t_philo *philo)
{
	pthread_t	dead_thread;

	pthread_create(&dead_thread, NULL, &check_death, philo);
	pthread_detach(dead_thread);
	philo->death_time = get_time() + philo->data->time_to_die;
	while (1)
	{
		think(philo);
		take_fork(philo);
		eat(philo);
		go_sleep(philo);
	}
}
