/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:31:47 by iayni             #+#    #+#             */
/*   Updated: 2022/06/21 21:31:51 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_eat(void *arg)
{
	t_all	*var;
	int		i;

	var = (t_all *)arg;
	i = -1;
	while (++i < var->num_philo)
	{
		sem_wait(var->towforks);
		usleep(100);
	}
	sem_post(var->main);
	return (0);
}

void	*check_death(void *arg)
{
	t_philo			*philo;
	int				i;
	unsigned int	now;

	i = -1;
	philo = (t_philo *)arg;
	while (philo->var->finish == 0)
	{
		now = get_time();
		if (now >= philo->death_time)
		{
			philo->var->finish = 1;
			print(philo, " is dead");
			sem_wait(philo->eat);
			sem_post(philo->var->main);
			while (++i < philo->var->must_eat)
				sem_post(philo->var->towforks);
		}
		usleep(100);
	}
	return (0);
}
