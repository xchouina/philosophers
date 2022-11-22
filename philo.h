/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xchouina <xchouina@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:43 by xchouina          #+#    #+#             */
/*   Updated: 2022/11/07 15:06:47 by xchouina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct ind_philo
{
	int				id;
	int				ate_nbr;
	int				last_meal;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	pthread_t		thr;
	pthread_t		death_thr;
	struct vars		*varg;
	bool			done_eating;

}	t_philos;

typedef struct vars
{
	int				nbr_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				min_eat;
	t_philos		*ph;
	int				status;
	bool			full;
	int				hmfe;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
	pthread_mutex_t	finish;
	pthread_mutex_t	is_eating;

	struct timeval	time;
}		t_vars;

// ----FUNCTIONS------
void	init_vars(t_vars *vars, int ac, char **av);
int		time_stamp(struct timeval time);
int		parsing(int ac, char **av);
int		ft_atoi(const char *str);
void	*death_thread(void *p);
int		am_i_dead(t_philos *ph, int i);
void	cleaning(t_vars *vars);
void	*routine(void *p);
void	philo_is_eating(t_philos *ph);
void	philo_is_sleeping(t_philos *ph);
void	philo_is_thinking(t_philos *ph);
void	smart_sleeep(t_philos *ph, int time);
#endif
