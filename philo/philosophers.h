/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:44:27 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/10 18:21:12 by sdos-san         ###   ########.fr       */
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

typedef struct philosophers
{
	unsigned int	phil_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	eat_count;
	unsigned int	last_eat;
	int				id;
	int				status;
	int				detach;
	pthread_mutex_t	*forks;
} t_philo;

/* UTILS */
unsigned int	ft_atoi(const char *str);

/* THREAD */

int				create_threads(int argc, char **argv, int philonum, pthread_t	*philos);
void			join_threads(int philonum, pthread_t	*philos);


/* ERRORS */

int				malloc_error(void);
int				create_thread_error(void);
int				mutex_error(void);

#endif