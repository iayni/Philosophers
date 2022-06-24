/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 21:45:37 by iayni             #+#    #+#             */
/*   Updated: 2022/06/24 21:45:37 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(unsigned long time)
{
	unsigned long now;

	now = get_time();
	while (get_time() - now < time)
		usleep(50);
}

void	init_forks(t_philo *philo, int i)
{
	if (i == 0)
	{
		pthread_mutex_lock(&philo->data->forks[(philo->id - 1)
		% philo->data->n_philo]);
		print(philo, "Taken a Fork", 1);
		pthread_mutex_lock(&philo->data->forks[(philo->id)
		% philo->data->n_philo]);
		print(philo, "Taken a Fork", 1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[(philo->id - 1)
		% philo->data->n_philo]);
		pthread_mutex_unlock(&philo->data->forks[(philo->id)
		% philo->data->n_philo]);
	}
}

void	*handler(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if(!(philo->id & 1))
		ft_usleep(philo->data->t_eat / 2);
	while (1)
	{
		init_forks(philo, 0);
		print(philo, "is Eating", 1);
		ft_usleep(philo->data->t_eat);
		init_forks(philo, 1);
		philo->time = get_time();
		print(philo, "is Sleeping", 1);
		ft_usleep(philo->data->t_sleep);
		print(philo, "is Thinking", 1);
		philo->ate += 1;
	}
}

void	thread_init(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->print, NULL);
	while (++i < data->n_philo)
		pthread_create(&data->philos[i].philo, NULL,
			handler, &data->philos[i]);
	i = -1;
	while (++i < data->n_philo)
		pthread_detach(data->philos[i].philo);
}