/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:31:55 by iayni             #+#    #+#             */
/*   Updated: 2022/06/21 21:31:58 by iayni            ###   ########.fr       */
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

static int	open_semaphores(t_all *var)
{
	var->forks = sem_open("forks", O_CREAT, 0644, var->num_philo);
	if (var->forks == SEM_FAILED)
		return (0);
	var->main = sem_open("main", O_CREAT, 0644, 0);
	if (var->main == SEM_FAILED)
		return (0);
	var->print = sem_open("print", O_CREAT, 0644, 1);
	if (var->print == SEM_FAILED)
		return (0);
	var->towforks = sem_open("towforks", O_CREAT, 0644, 0);
	if (var->towforks == SEM_FAILED)
		return (0);
	return (1);
}

static int	philo_fill(t_all *var)
{
	int			i;
	int			id;
	pthread_t	tmp;

	i = -1;
	var->creat_date = get_time();
	if (var->must_eat > 0)
	{
		pthread_create(&tmp, NULL, &check_eat, var);
		pthread_detach(tmp);
	}
	while (++i < var->num_philo)
	{
		var->philos[i].n = i;
		var->philos[i].var = var;
		var->philos[i].death_time = get_time() + var->time_to_die;
		var->philos[i].eat = sem_open("eat", O_CREAT, 0644, 1);
		if (var->print == SEM_FAILED)
			return (3);
		id = fork();
		if (id == 0)
			monitor(&var->philos[i]);
		var->philos[i].id = id;
	}
	return (0);
}

int	data_fill(int ac, char **av, t_all *var)
{
	var->num_philo = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		var->must_eat = ft_atoi(av[5]);
	else
		var->must_eat = 0;
	var->philos = ft_calloc(var->num_philo, sizeof(t_philo));
	if (!var->philos)
		return (2);
	if (!open_semaphores(var))
		return (3);
	return (philo_fill(var));
}
