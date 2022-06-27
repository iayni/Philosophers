/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:42:32 by iayni             #+#    #+#             */
/*   Updated: 2022/06/26 20:42:32 by iayni            ###   ########.fr       */
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
	int				id;
	int				num_eat;
	unsigned int	death_time;
	struct s_data	*data;
	sem_t			*eat;
	pthread_t		thread;
}		t_philo;

typedef struct s_data
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
	sem_t			*twoforks;
	unsigned int	creat_date;
	t_philo			*philos;
}		t_data;

int				check_args(int ac, char **av);
int				end_program(int err, t_data *data);
void			unlink_sem(void);
void			clean_exit(t_data *data);
void			print(t_philo *philo, char *str);
void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(char *str);
int				fill_data(int ac, char **av, t_data *data);
void			monitor(t_philo *philo);
void			*check_eat(void *arg);
void			*check_death(void *arg);
unsigned int	get_time(void);

#endif