/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:45:27 by iayni             #+#    #+#             */
/*   Updated: 2022/06/24 21:45:27 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philo;
	long long		time;
	int				id;
	int				ate;
	struct s_data	*data;		
}		t_philo;

typedef struct s_data
{
	int					lamp;
	long long			time;
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	pthread_mutex_t		print;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}	t_data;

int		allocate(t_data *data, char **av);
int		ft_atoi(char *str);
int		check_args(int ac, char **av);
void	thread_init(t_data *data);
void	init_forks(t_philo *philo, int i);
void	*handler(void *arg);
void	ft_usleep(unsigned long time);
void	*manage(t_data *data);
int		must_eat(int *c, t_philo *philo);
void	print(t_philo *philo, char *str, int n);
long long	get_time(void);

#endif