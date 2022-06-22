/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:32:15 by iayni             #+#    #+#             */
/*   Updated: 2022/06/21 21:32:19 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_philo
{
	int				n;
	int				n1;
	int				id;
	int				num_eat;
	unsigned int	death_time;
	struct s_all	*var;
	sem_t			*eat;
	pthread_t		thread;
}		t_philo;

typedef struct s_all
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				finish;
	int				eat_finish;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*main;
	sem_t			*towforks;
	unsigned int	creat_date;
	t_philo			*philos;
}		t_all;

void			unlink_sem(void);
void			clean_exit(t_all *var);
int				check_args(int ac, char **av);
void			*check_death(void *arg);
void			*check_eat(void *arg);
int				data_fill(int ac, char **av, t_all *var);
unsigned int	get_time(void);
int				end_program(int err, t_all *var);
void			monitor(t_philo *philo);
void			print(t_philo *philo, char *str);
int				ft_atoi(char *str);
void			*ft_calloc(size_t count, size_t size);

#endif