/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchouina <xchouina@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:59:10 by xchouina          #+#    #+#             */
/*   Updated: 2022/11/15 13:17:58 by xchouina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*death_thread(void *p)
{
	t_philos	*ph;

	ph = (t_philos *)p;
	smart_sleeep(ph, (ph->varg->t_die + 1));
	pthread_mutex_lock(&ph->varg->is_eating);
	pthread_mutex_lock(&ph->varg->finish);
	if (!am_i_dead(ph, 0) && ph->done_eating == false
		&& (time_stamp(ph->varg->time) - ph->last_meal) >= ph->varg->t_die)
	{
		pthread_mutex_lock(&ph->varg->write);
		if (!am_i_dead(ph, 0))
			printf("\033[31m%d ms: %d has died. 😵\n\033[0m",
				time_stamp(ph->varg->time), ph->id);
		pthread_mutex_unlock(&ph->varg->write);
		am_i_dead(ph, 1);
	}
	pthread_mutex_unlock(&ph->varg->is_eating);
	pthread_mutex_unlock(&ph->varg->finish);
	return (NULL);
}

int	am_i_dead(t_philos *ph, int i)
{
	pthread_mutex_lock(&ph->varg->death);
	if (i != 0)
		ph->varg->status = i;
	if (ph->varg->status != 0)
	{
		pthread_mutex_unlock(&ph->varg->death);
		return (1);
	}
	pthread_mutex_unlock(&ph->varg->death);
	return (0);
}

void	cleaning(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->nbr_philos)
		pthread_join(vars->ph[i].thr, NULL);
	pthread_mutex_destroy(&vars->death);
	pthread_mutex_destroy(&vars->write);
	pthread_mutex_destroy(&vars->finish);
	pthread_mutex_destroy(&vars->is_eating);
	i = 0;
	while (i < vars->nbr_philos)
		pthread_mutex_destroy(&vars->ph[i++].lfork);
	if (vars->full == true)
		printf("Philos are full\n");
	free(vars->ph);
}

// 1 800 200 200 	should die at 801
// 5 800 200 200 	no one dies
// 5 800 200 200 7 	everyone eat 7 times
// 4 410 200 200 	no one dies
// 4 310 200 100 	someone should die
