/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iayni <iayni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:31:42 by iayni             #+#    #+#             */
/*   Updated: 2022/06/21 21:31:45 by iayni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	check_num(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == 0)
			return (1);
		while (av[i][j])
		{
			if (av[i][j] == '-')
				j++;
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	valid_arg(int ac, char **av)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0)
		return (1);
	if (ft_atoi(av[4]) < 0)
		return (1);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (1);
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	if (valid_arg(ac, av))
		return (1);
	return (check_num(ac, av));
}
