/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:46:50 by iayni             #+#    #+#             */
/*   Updated: 2022/06/23 21:56:44 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, unsigned long time, char *doing)
{
	pthread_mutex_lock(philo->print);
    printf("%lums %d %s\n", time, philo->id, doing);
	pthread_mutex_unlock(philo->print);
}

void    *init_data(void *args)
{
    t_philo *philo;
    
    philo = (t_philo *)args;
    if(philo->id % 2 == 0)
        usleep(10);
    philo->last_meal = in_time();
    while (1)
    {
        pthread_mutex_lock(&philo->fork[philo->id - 1]);
        print(philo, real_time(philo), "has Taken a Fork");
        pthread_mutex_lock(&philo->fork[philo->id % philo->var->num_philo]);
        print(philo, real_time(philo), "has Taken a Fork");
        print(philo, real_time(philo), "is Eating");
        philo->ate++;
        if (philo->ate == philo->var->must_eat)
            philo->var->total_ate++;
        usleep(philo->var->t_eat * 1000);
        philo->last_meal = in_time();
        pthread_mutex_unlock(&philo->fork[philo->id - 1]);
        pthread_mutex_unlock(&philo->fork[philo->id % philo->var->num_philo]);
        print(philo, real_time(philo), "is Sleeping");
        usleep(philo->var->t_sleep * 1000);
        print(philo, real_time(philo), "is Thinking");        
    }
	return (0);
}

void	ft(t_philo *philo, t_data *var)
{
	int i;
	
	i = 0;
	while (1)
	{
		if (philo[i].var->total_ate == philo[i].var->num_philo)
		{
			dst_mutex(philo);
			free_param(philo, philo->fork, var);
			return ;
		}
		if (in_time() - philo[i].last_meal 
			> (unsigned long)var->t_die)
		{
			usleep(100);
			pthread_mutex_lock(philo->print);
			printf("%lums %d died\n", real_time(philo), philo->id);
			dst_mutex(philo);
			free_param(philo, philo->fork, var);
			return ;
		}
		i = (i + 1) % var->num_philo;
		usleep(100);
	}
}

int	exit_error(void)
{
	printf("Something Wrong!!\n");
	return (1);
}

int	main(int ac, char **av)
{
	t_data		*var;
	t_philo		*philo;
	pthread_t	*thread;
	int 		i;

	if (ac != 5 && ac != 6)
		return (exit_error());
	var = (t_data *)malloc(sizeof(t_data));
	if (arg_to_param(var, av))
		return (free_param(0, 0, var));
	philo = (t_philo *)malloc(sizeof(t_philo) * var->num_philo);
	if (init_param(philo, var))
		return (1);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * var->num_philo);
	i = -1;
	while (++i < philo->var->num_philo)
	{
		pthread_create(&thread[i], NULL, init_data, philo + i);
		usleep(100);
	}
	ft(philo,var);
	free(thread);
	return (0);
}
