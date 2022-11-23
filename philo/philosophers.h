/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:44:27 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/23 18:43:13 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef struct shared
{
	unsigned int	phil_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	eat_max;
	long long	 	begin_time;
	int				pestilence;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	pthread_mutex_t printf;
} t_shared;

typedef struct philosophers
{
	unsigned int	eat_count;
	long long	 	last_eat;
	int				id;
	int				status;
	t_shared		*global;
} t_philo;

/* UTILS */

int			ft_iswhitespace(int ch);
int			ft_isdigit(int ch);
size_t		ft_strlen(const char *str);
long int	ft_atoi(const char *str);

void		join_threads(t_shared *shared);
void		destroy_mutexes(t_shared *shared);
void		create_mutex(t_shared *shared);
void		initialize_shared(t_shared *shared, int argc, char **argv);
int			create_threads(int argc, char **argv, int philonum, pthread_t	*philos);
void		*life(void *id);


int			malloc_error(void);
int			create_thread_error(void);
int			mutex_error(void);

t_philo		*initialize_id(int i, t_philo *id, t_shared *global);
void		free_all(t_shared *shared, t_philo *id);


#endif