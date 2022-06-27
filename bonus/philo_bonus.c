/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:41:59 by iayni             #+#    #+#             */
/*   Updated: 2022/06/26 20:41:59 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		kill(data->philos[i].id, SIGKILL);
	sem_close(data->forks);
	sem_close(data->main);
	sem_close(data->print);
	sem_close(data->twoforks);
	sem_unlink("forks");
	sem_unlink("twoforks");
	sem_unlink("main");
	sem_unlink("print");
	sem_unlink("eat");
	free(data->philos);
	exit(EXIT_SUCCESS);
}

void	unlink_sem(void)
{
	sem_unlink("eat");
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("main");
	sem_unlink("twoforks");
}

int	main(int ac, char **av)
{
	t_data	data;
	int		error;

	memset(&data, 0, sizeof(t_data));
	error = check_args(ac, av);
	if (error)
		return (end_program(error, &data));
	unlink_sem();
	error = fill_data(ac, av, &data);
	if (error)
		return (end_program(error, &data));
	sem_wait(data.main);
	clean_exit(&data);
	puts("end");
	return (0);
}
