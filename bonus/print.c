/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:32:22 by iayni             #+#    #+#             */
/*   Updated: 2022/06/21 21:32:24 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print(t_philo *philo, char *str)
{
	unsigned int	now;

	now = get_time();
	sem_wait(philo->var->print);
	printf("%ums %d %s\n", now - philo->var->creat_date, philo->n + 1, str);
	if (philo->var->finish == 1)
		return ;
	sem_post(philo->var->print);
}
