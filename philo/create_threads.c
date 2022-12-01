/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:27:27 by sdos-san          #+#    #+#             */
/*   Updated: 2022/12/01 11:02:07 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Create the threads, one thread for each philosopher
   This function also initialize the values */

int	create_threads(int argc, char **argv, int philonum, pthread_t	*philos)
{
	int			i;
	t_philo		*id;
	t_shared	shared;
	pthread_t	assasin;

	i = 0;
	initialize_shared(&shared, argc, argv);
	shared.philos = philos;
	id = malloc(sizeof(t_philo) * philonum);
	if (!id)
		return (malloc_error());
	if (pthread_create(&assasin, NULL, &finish_them, &shared))
		return (create_thread_error());
	while (i < philonum)
	{
		initialize_id(i, &id[i], &shared);
		if (pthread_create(&philos[i], NULL, &life, &id[i]))
			return (create_thread_error());
		i++;
	}
	join_threads(&shared, assasin);
	destroy_mutexes(&shared);
	free_all(&shared, id);
	return (0);
}

/*Initialize the shared struct between the philosphers*/

void	initialize_shared(t_shared *shared, int argc, char **argv)
{
	int				i;

	i = 0;
	shared->phil_num = ft_atoi(argv[1]);
	shared->time_to_die = ft_atoi(argv[2]);
	shared->time_to_eat = ft_atoi(argv[3]);
	shared->time_to_sleep = ft_atoi(argv[4]);
	shared->eat_max = -1;
	shared->pestilence = 1;
	shared->begin_time = get_begin_time();
	shared->eaten_times = malloc(sizeof(long long) * shared->phil_num);
	shared->eat_count = malloc(sizeof(int) * shared->phil_num);
	while (i < (int)shared->phil_num)
	{
		shared->eaten_times[i] = 0;
		shared->eat_count[i] = 0;
		i++;
	}
	if (argc == 6)
		shared->eat_max = ft_atoi(argv[5]);
	create_mutex(shared);
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

/* Join all the threads and free its resources*/

void	join_threads(t_shared *shared, pthread_t assasin)
{
	int	i;

	i = 0;
	while (i < (int)shared->phil_num)
	{
		pthread_join(shared->philos[i], NULL);
		i++;
	}
	pthread_join(assasin, NULL);
}

/* STATUS CODE 0 - WANTS TO EAT, DID NOT PRINT THAT IS THINKING */
/* STATUS CODE 1 - WANTS TO EAT, ALREADY PRINT THAT IS THINKING */
/* STATUS CODE 2 - IS EATING, READY TO SLEEP */

t_philo	*initialize_id(int i, t_philo *id, t_shared *global)
{
	id->global = global;
	id->id = i;
	id->status = 0;
	id->first = (id->id + 1) % id->global->phil_num;
	id->second = id->id;
	if (id->id % 2 == 0)
	{
		id->first = id->id;
		id->second = (id->id + 1) % id->global->phil_num;
	}
	return (id);
}
