/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:46:41 by iayni             #+#    #+#             */
/*   Updated: 2022/06/21 21:24:57 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	int				num_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				total_ate;
	unsigned long	time;
}	t_data;

typedef struct s_philo
{
    int				id;
	int				ate;
    t_data			*var;
    pthread_mutex_t	*fork;
    pthread_mutex_t *print;
    unsigned long	last_meal;
}	t_philo;

int	exit_error(void);
void    *init_data(void *args);
void	print(t_philo *philo, unsigned long time, char *doing);
unsigned long real_time(t_philo *philo);
unsigned long   in_time(void);
void    dst_mutex(t_philo *philo);
int	ft_atoi(char *str);
void    assign_param(t_philo *philo, t_data *var, pthread_mutex_t *fork,
                    pthread_mutex_t *print);
int free_param(t_philo *philo, pthread_mutex_t *fork, t_data *var);
int init_param(t_philo *philo, t_data *var);
int check_args(char **av);
int arg_to_param(t_data *var, char **av);
void	ft(t_philo *philo, t_data *var);
#endif