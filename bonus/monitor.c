/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:32:06 by iayni             #+#    #+#             */
/*   Updated: 2022/06/21 21:32:08 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_fork(t_philo *philo)
{
	sem_wait(philo->var->forks);
	print(philo, "has taken a fork");
	sem_wait(philo->var->forks);
	print(philo, "has taken a fork");
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->eat);
	print(philo, "is eating");
	philo->death_time = get_time() + philo->var->time_to_die;
	philo->num_eat++;
	if (philo->var->must_eat > 0
		&& philo->num_eat == philo->var->must_eat)
		sem_post(philo->var->towforks);
	sem_post(philo->eat);
	usleep(philo->var->time_to_eat * 1000);
	sem_post(philo->var->forks);
	sem_post(philo->var->forks);
}

static void	go_sleep(t_philo *philo)
{
	print(philo, "sleeping");
	usleep(philo->var->time_to_sleep * 1000);
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
	philo->death_time = get_time() + philo->var->time_to_die;
	while (1)
	{
		think(philo);
		take_fork(philo);
		eat(philo);
		go_sleep(philo);
	}
}
