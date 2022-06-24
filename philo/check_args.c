/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 21:45:42 by iayni             #+#    #+#             */
/*   Updated: 2022/06/24 21:45:42 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int		check_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
		if(ft_atoi(av[i]) < 1)
			return (printf("Parsing Error!!\n"), 0);
	return (1);
}

int	must_eat(int *c, t_philo *philo)
{
	if(philo->ate >= philo->data->n_eat)
		*c += 1;
		if (* c == philo->data->n_philo)
		{
			print(philo, NULL, 0);
			return (0);
		}
		return (1);
}

void	*manage(t_data *data)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (1)
	{
		if (i == data->n_philo)
		{
			i = 0;
			c = 0;
		}
		if (data->n_eat)
			if (!must_eat(&c, &data->philos[i]))
				return (NULL);
		if ((get_time () - data->philos[i].time) >= data->t_die)
		{
			print(&data->philos[i], "Died", 0);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}