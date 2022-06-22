/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:32:02 by iayni             #+#    #+#             */
/*   Updated: 2022/06/21 21:32:04 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sem_error(t_all *var)
{
	if (var->philos)
		free(var->philos);
	if (var->forks != SEM_FAILED)
		sem_close(var->forks);
	if (var->main != SEM_FAILED)
		sem_close(var->main);
	if (var->print != SEM_FAILED)
		sem_close(var->print);
}

static void	malloc_error(t_all *var)
{
	if (var->philos)
		free(var->philos);
	write(2, "Error: Malloc Failed\n", 19);
}

int	end_program(int err, t_all *var)
{
	if (err == 1)
		write (2, "Error: Wrong Arguments\n", 24);
	if (err == 2)
		malloc_error(var);
	if (err == 3)
		sem_error(var);
	return (1);
}
