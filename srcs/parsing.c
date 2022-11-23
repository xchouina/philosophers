/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchouina <xchouina@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:34:36 by xchouina          #+#    #+#             */
/*   Updated: 2022/11/22 15:09:24 by xchouina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	parsing_min_max(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) > 9999)
		{
			printf("Argument is too big :/\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	parsing(int ac, char **av)
{
	int	i;
	int	res;

	res = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Invalid number of arguments. Please, be better.\n");
		res = -1;
	}
	i = 1;
	while (i < ac)
	{
		if (ft_strisdigit(av[i]) == 0)
		{
			printf("Arguments must be positive numbers. \n");
			res = -1;
		}
		i++;
	}
	if (parsing_min_max(ac, av) == -1)
		res = -1;
	if (res == -1)
		return (-1);
	else
		return (0);
}
