/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:32:11 by iayni             #+#    #+#             */
/*   Updated: 2022/06/21 21:32:12 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

void	clean_exit(t_all *var)
{
	int	i;

	i = -1;
	while (++i < var->num_philo)
		kill(var->philos[i].id, SIGKILL);
	sem_close(var->forks);
	sem_close(var->main);
	sem_close(var->print);
	sem_close(var->towforks);
	sem_unlink("forks");
	sem_unlink("towforks");
	sem_unlink("main");
	sem_unlink("print");
	sem_unlink("eat");
	free(var->philos);
	exit(EXIT_SUCCESS);
}

void	unlink_sem(void)
{
	sem_unlink("eat");
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("main");
	sem_unlink("towforks");
}

int	main(int ac, char **av)
{
	t_all	var;
	int		error;

	memset(&var, 0, sizeof(t_all));
	error = check_args(ac, av);
	if (error)
		return (end_program(error, &var));
	unlink_sem();
	error = data_fill(ac, av, &var);
	if (error)
		return (end_program(error, &var));
	sem_wait(var.main);
	clean_exit(&var);
	puts("end");
	return (0);
}
