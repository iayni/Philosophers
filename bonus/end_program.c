/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:56:49 by iayni             #+#    #+#             */
/*   Updated: 2022/06/26 20:56:49 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sem_error(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->main != SEM_FAILED)
		sem_close(data->main);
	if (data->print != SEM_FAILED)
		sem_close(data->print);
	if (data->twoforks != SEM_FAILED)
		sem_close(data->twoforks);
}

static void	malloc_error(t_data *data)
{
	if (data->philos)
		free(data->philos);
	write(2, "Error: Failed to allocate\n", 27);
}

int	end_program(int err, t_data *data)
{
	if (err == 1)
		write (2, "Error: Wrong Arguments\n", 24);
	if (err == 2)
		malloc_error(data);
	if (err == 3)
		sem_error(data);
	return (1);
}

void	print(t_philo *philo, char *str)
{
	unsigned int	daba;

	daba = get_time();
	sem_wait(philo->data->print);
	printf("%ums %d %s\n", daba - philo->data->creat_date, philo->n + 1, str);
	if (philo->data->finish == 1)
		return ;
	sem_post(philo->data->print);
}
