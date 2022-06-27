/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:56:36 by iayni             #+#    #+#             */
/*   Updated: 2022/06/26 20:56:36 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	time.tv_sec = time.tv_sec * 1000;
	time.tv_usec = time.tv_usec / 1000;
	return (time.tv_usec + time.tv_sec);
}

static int	philo_fill(t_data *data)
{
	int			i;
	int			id;
	pthread_t	tmp;

	i = -1;
	data->creat_date = get_time();
	if (data->must_eat > 0)
	{
		pthread_create(&tmp, NULL, &check_eat, data);
		pthread_detach(tmp);
	}
	while (++i < data->num_philo)
	{
		data->philos[i].n = i;
		data->philos[i].data = data;
		data->philos[i].death_time = get_time() + data->time_to_die;
		data->philos[i].eat = sem_open("eat", O_CREAT, 0644, 1);
		if (data->print == SEM_FAILED)
			return (3);
		id = fork();
		if (id == 0)
			monitor(&data->philos[i]);
		data->philos[i].id = id;
	}
	return (0);
}

static int	open_semaphores(t_data *data)
{
	data->forks = sem_open("forks", O_CREAT, 0644, data->num_philo);
	if (data->forks == SEM_FAILED)
		return (0);
	data->main = sem_open("main", O_CREAT, 0644, 0);
	if (data->main == SEM_FAILED)
		return (0);
	data->print = sem_open("print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (0);
	data->twoforks = sem_open("twoforks", O_CREAT, 0644, 0);
	if (data->twoforks == SEM_FAILED)
		return (0);
	return (1);
}

int	fill_data(int ac, char **av, t_data *data)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = 0;
	data->philos = ft_calloc(data->num_philo, sizeof(t_philo));
	if (!data->philos)
		return (2);
	if (!open_semaphores(data))
		return (3);
	return (philo_fill(data));
}
