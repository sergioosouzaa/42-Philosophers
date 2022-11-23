/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:27:27 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/23 18:42:55 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Create the threads, one thread for each philosopher
   This function also initialize the values */
//FREE PHILOS, FREE ID

int	create_threads(int argc, char **argv, int philonum, pthread_t	*philos)
{
	int			i;
	t_philo		*id;
	t_shared	shared;

	i = 0;
	initialize_shared(&shared, argc, argv);
	shared.philos = philos;
	id = malloc(sizeof(t_philo) * philonum);
	if (!id)
		return (malloc_error());
	while (i < philonum)
	{
		initialize_id(i, &id[i], &shared);
		if (pthread_create(&philos[i], NULL, &life, &id[i]))
			return (create_thread_error());
		i++;
	}
	join_threads(&shared);
	destroy_mutexes(&shared);
	free_all(&shared, id);
	return (0);
}

/*Initialize the shared struct between the philosphers*/

void	initialize_shared(t_shared *shared, int argc, char **argv)
{
	struct timeval	begin_time;

	gettimeofday(&begin_time, NULL);
	shared->phil_num = ft_atoi(argv[1]);
	shared->time_to_die = ft_atoi(argv[2]);
	shared->time_to_eat = ft_atoi(argv[3]);
	shared->time_to_sleep = ft_atoi(argv[4]);
	shared->eat_max = -1;
	shared->pestilence = 0;
	if (argc == 6)
		shared->eat_max = ft_atoi(argv[5]);
	create_mutex(shared);
	shared->begin_time = begin_time.tv_sec / 1000 + begin_time.tv_usec * 0.001;
}

/*Initialize all the mutexes*/

void	create_mutex(t_shared *shared)
{
	int	i;

	shared->forks = malloc(shared->phil_num * sizeof(pthread_mutex_t));
	if (!shared->forks)
	{
		malloc_error();
		return ;
	}
	i = 0;
	while (i < (int)shared->phil_num)
	{
		pthread_mutex_init(&shared->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&shared->printf, NULL);
	pthread_mutex_init(&shared->death, NULL);
}

/*Destroy all the mutexes and free the malloc forks*/

void	destroy_mutexes(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < (int)shared->phil_num)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		i++;
	}
	free(shared->forks);
	pthread_mutex_destroy(&shared->printf);
	pthread_mutex_destroy(&shared->death);
}

/* Free all things*/

void	free_all(t_shared *shared, t_philo *id)
{
	free(shared->philos);
	free(id);
}

/* Join all the threads and free its resources*/

void	join_threads(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < (int)shared->phil_num)
	{
		pthread_join(shared->philos[i], NULL);
		i++;
	}
}

// STATUS CODE 0 - WANTS TO EAT, DID NOT PRINT THAT IS THINKING
// STATUS CODE 1 - WANTS TO EAT, ALREADY PRINT THAT IS THINKING
// STATUS CODE 2 - IS EATING, READY TO SLEEP

t_philo	*initialize_id(int i, t_philo *id, t_shared *global)
{
	id->last_eat = 0;
	id->eat_count = 0;
	id->global = global;
	id->id = i;
	id->status = 0;
	return (id);
}