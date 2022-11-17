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

void	*angel_of_death(void *p)
{
	t_philos	*ph;

	ph = (t_philos *)p;
	smart_sleeep(ph, (ph->varg->t_die + 1));
	pthread_mutex_lock(&ph->varg->is_eating);
	pthread_mutex_lock(&ph->varg->finish);
	if (!am_i_dead(ph, 0) && ph->ate_nbr != ph->varg->min_eat
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
