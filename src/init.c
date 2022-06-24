/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 23:22:26 by iayni             #+#    #+#             */
/*   Updated: 2022/06/23 21:57:56 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(char **av)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if((av[i][j] < '0' || av[i][j] > '9') && j != 0)
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int arg_to_param(t_data *var, char **av)
{
    if(check_args(av) )
        return (exit_error());
    var->total_ate = 0;
    var->time = in_time();
    var->num_philo = ft_atoi(av[1]);
    var->t_die = ft_atoi(av[2]);
    var->t_eat = ft_atoi(av[3]);
    var->t_sleep = ft_atoi(av[4]);
    if (var->num_philo <= 0 || var->t_die <= 0 || var->t_eat <= 0 
            || var->t_sleep <= 0)
        return (1);
    if (av[5])
    {
        var->must_eat = ft_atoi(av[5]);
        if(var->must_eat <= 0)
            return (1);
    }
    else
        var->must_eat = -1;
    return (0);    
}

void    assign_param(t_philo *philo, t_data *var, pthread_mutex_t *fork,
                    pthread_mutex_t *print)
{
    int i;

    i = 0;
    while (i < var->num_philo)
    {
        philo[i].ate = 0;
        philo[i].var = var;
        philo[i].fork = fork;
        philo[i].print = print;
        philo[i].id = i + 1;
        i++;
    }
}

int free_param(t_philo *philo, pthread_mutex_t *fork, t_data *var)
{
    if (philo)
        free(philo);
    if (fork)
        free(fork);
    if (var)
        free(var);
    return (1);
}

int init_param(t_philo *philo, t_data *var)
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				i;

	i = 0;
    fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->num_philo);
    if (!fork || !philo)
        return ( free_param(philo, fork, var));
    while (i < var->num_philo)
        if (pthread_mutex_init(&fork[i++], 0))
            return ( free_param(philo, fork, var));
    if (pthread_mutex_init(&print, 0))
        return ( free_param(philo, fork, var));
    assign_param(philo, var, fork, &print);
    return (0);
}
