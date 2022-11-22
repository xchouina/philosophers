/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchouina <xchouina@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:59:10 by xchouina          #+#    #+#             */
/*   Updated: 2022/11/22 13:46:30 by xchouina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *p)
{
	t_philos	*ph;

	ph = (t_philos *)p;
	while (!am_i_dead(ph, 0))
	{
		pthread_create(&ph->death_thr, NULL, death_thread, ph);
		philo_is_eating(ph);
		philo_is_sleeping(ph);
		pthread_detach(ph->death_thr);
		if (++ph->ate_nbr == ph->varg->min_eat)
		{
			pthread_mutex_lock(&ph->varg->finish);
			ph->done_eating = true;
			ph->varg->hmfe++;
			if (ph->varg->hmfe == ph->varg->nbr_philos)
				ph->varg->full = true;
			pthread_mutex_unlock(&ph->varg->finish);
			return (NULL);
		}
	}
	return (NULL);
}

void	philo_is_eating(t_philos *ph)
{
	if (ph->id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&ph->lfork);
	pthread_mutex_lock(&ph->varg->write);
	if (!am_i_dead(ph, 0))
		printf("%d ms: %d has taken a fork. 🍴\n",
			time_stamp(ph->varg->time), ph->id);
	pthread_mutex_unlock(&ph->varg->write);
	if (ph->varg->nbr_philos == 1)
	{
		smart_sleeep(ph, ph->varg->t_die + 10);
		pthread_mutex_unlock(&ph->lfork);
	}
	pthread_mutex_lock(ph->rfork);
	pthread_mutex_lock(&ph->varg->write);
	if (!am_i_dead(ph, 0))
		printf("%d ms: %d is eating. 🍝\n", time_stamp(ph->varg->time), ph->id);
	pthread_mutex_unlock(&ph->varg->write);
	pthread_mutex_lock(&ph->varg->is_eating);
	ph->last_meal = time_stamp(ph->varg->time);
	pthread_mutex_unlock(&ph->varg->is_eating);
	smart_sleeep(ph, ph->varg->t_eat);
	pthread_mutex_unlock(ph->rfork);
	pthread_mutex_unlock(&ph->lfork);
}

void	philo_is_sleeping(t_philos *ph)
{
	pthread_mutex_lock(&ph->varg->write);
	if (!am_i_dead(ph, 0))
		printf("%d ms: %d is sleeping. 😴\n", time_stamp(ph->varg->time), ph->id);
	pthread_mutex_unlock(&ph->varg->write);
	smart_sleeep(ph, ph->varg->t_sleep);
	pthread_mutex_lock(&ph->varg->write);
	if (!am_i_dead(ph, 0))
		printf("%d ms: %d is thinking. 🤔\n", time_stamp(ph->varg->time), ph->id);
	pthread_mutex_unlock(&ph->varg->write);
}

void	smart_sleeep(t_philos *ph, int time)
{
	int	now;

	now = time_stamp(ph->varg->time);
	while (time_stamp(ph->varg->time) - now < time)
		usleep(100);
}
