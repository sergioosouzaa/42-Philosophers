/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:44:27 by sdos-san          #+#    #+#             */
/*   Updated: 2022/12/01 13:30:00 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct philosophers
{
	int				id;
	int				status;
	int				eat_count;
	int				fork_num;
	int				pid;
	long long		time;
	long long		begin_time;
	long long		eaten_times;
	unsigned int	phil_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	eat_max;
	sem_t			*die;
	sem_t			*forks;
	sem_t			*print;
}	t_philo;

/* UTILS */

int			ft_iswhitespace(int ch);
int			ft_isdigit(int ch);
size_t		ft_strlen(const char *str);
long int	ft_atoi(const char *str);

void		initialize_id(t_philo *philo, int argc, char **argv, int id);


int			create_philo(int argc, char **argv, \
							int philonum);
void		*life(void *id);

int			malloc_error(void);
int			create_thread_error(void);
int			mutex_error(void);


void		free_all(t_philo *id);

void		my_print(t_philo	*temp, int code);
// long long	time_diff(t_shared *temp, struct timeval last_eat);
// void		create_assasin(t_shared	shared, pthread_t	assasin);

void		*finish_them(void *data);

long long	ft_return_time(long long begin_time);
long long	get_begin_time(void);

void		philo_eat(t_philo	*philo);
void		philo_think(t_philo	*philo);
void		philo_sleep(t_philo	*philo);
void		my_sleep(t_philo *philo, unsigned int militime);

#endif