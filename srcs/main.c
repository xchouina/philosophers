/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchouina <xchouina@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:04:02 by xchouina          #+#    #+#             */
/*   Updated: 2022/11/22 09:53:02 by xchouina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// ./philo 4 410 200 200 12

void	init_ph(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->nbr_philos)
	{
		vars->ph[i].varg = vars;
		vars->ph[i].id = i + 1;
		vars->ph[i].ate_nbr = 0;
		vars->ph[i].last_meal = 0;
		pthread_mutex_init(&vars->ph[i].lfork, NULL);
		if (i == vars->nbr_philos - 1)
			vars->ph[i].rfork = &vars->ph[0].lfork;
		else
			vars->ph[i].rfork = &vars->ph[i + 1].lfork;
		i++;
	}
}

void	init_vars(t_vars *vars, int ac, char **av)
{
	vars->nbr_philos = ft_atoi(av[1]);
	vars->ph = malloc(sizeof(t_philos) * vars->nbr_philos);
	vars->t_die = ft_atoi(av[2]);
	vars->t_eat = ft_atoi(av[3]);
	vars->t_sleep = ft_atoi(av[4]);
	vars->min_eat = -1;
	vars->status = 0;
	vars->hmfe = 0;
	pthread_mutex_init(&vars->death, NULL);
	pthread_mutex_init(&vars->write, NULL);
	pthread_mutex_init(&vars->finish, NULL);
	pthread_mutex_init(&vars->is_eating, NULL);
	if (ac == 6)
		vars->min_eat = ft_atoi(av[5]);
	gettimeofday(&vars->time, NULL);
	init_ph(vars);
}

int	time_stamp(struct timeval time)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - time.tv_sec) * 1000
		+ (now.tv_usec - time.tv_usec) / 1000);
}

void	philo_threads(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->nbr_philos)
		pthread_create(&vars->ph[i].thr, NULL, routine, &vars->ph[i]);
	i = 0;
	while (i < vars->nbr_philos)
		pthread_join(vars->ph[i++].thr, NULL);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (parsing(ac, av) == -1)
		return (0);
	init_vars(&vars, ac, av);
	philo_threads(&vars);
	return (1);
}
