/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:45:18 by iayni             #+#    #+#             */
/*   Updated: 2022/06/24 21:45:18 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate(t_data *data, char **av)
{
	int	i;

	i = -1;
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (av[5])
		data->n_eat = ft_atoi(av[5]);
	data->philos = malloc(sizeof(t_philo) * (data->n_philo));
	if (!data->philos)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (free(data->philos), 0);
	data->time = get_time();
	while (++i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].id = i + 1;
		data->philos[i].ate = 0;
		data->philos[i].data = data;
		data->philos[i].time = data->time;
	}
	return (1);
}

int	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->print));
	free(data->philos);
	free(data->forks);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if ((ac == 5 || ac == 6) && check_args(ac, av))
	{
		if (!allocate(&data, av))
			return (printf("Error !! Allocating\n"), 0);
		thread_init(&data);
		manage(&data);
		return (free_all(&data), 0);
	}
}
