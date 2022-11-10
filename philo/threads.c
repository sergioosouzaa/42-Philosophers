/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:37:56 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/10 18:21:29 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo	*philo)
{
	struct timeval 	start;
	unsigned int	time;
	unsigned int	hungry_time;

	gettimeofday(&start, NULL);
	time = start.tv_usec;
	hungry_time = time - philo->last_eat;
	if (hungry_time > philo->time_to_die)
		return(0);
	return (1);
}
void	print_pick_fork(int id)
{
    struct timeval 	start;
	gettimeofday(&start, NULL);
	printf("%d %d pick up a fork\n", start.tv_usec, id + 1);
}

void	print_put_fork(int id)
{
    struct timeval 	start;
	gettimeofday(&start, NULL);
	printf("%d %d put down a fork\n", start.tv_usec, id + 1);
}

void	eating(t_philo	*philo)
{
    struct timeval 	start;
	unsigned int	time_eat;

	gettimeofday(&start, NULL);
	time_eat = start.tv_usec;
	philo->last_eat = time_eat + philo->time_to_eat;
	philo->eat_count = philo->eat_count + 1;
	printf("%d %d is eating\n", start.tv_usec, philo->id + 1);
	philo->status = 2;
	usleep(philo->time_to_eat);
}


void	pick_fork(t_philo	*philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[(philo->id)]);
		print_pick_fork(philo->id);
		pthread_mutex_lock(&philo->forks[(philo->id + 1) % philo->phil_num]);
		print_pick_fork(philo->id);
		eating(philo);
		pthread_mutex_unlock(&philo->forks[(philo->id + 1) % philo->phil_num]);
		print_put_fork(philo->id);
		pthread_mutex_unlock(&philo->forks[(philo->id)]);
		print_put_fork(philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[(philo->id + 1) % philo->phil_num]);
		print_pick_fork(philo->id);
		pthread_mutex_lock(&philo->forks[(philo->id)]);
		print_pick_fork(philo->id);
		eating(philo);
		pthread_mutex_unlock(&philo->forks[(philo->id)]);
		print_put_fork(philo->id);
		pthread_mutex_unlock(&philo->forks[(philo->id + 1) % philo->phil_num]);
		print_put_fork(philo->id);
	}
}

void	*routine(void *id)
{
	t_philo			*temp;
    struct timeval 	start;

	temp = (t_philo *)id;
	while(1)
	{
		if (temp->status == 0)
		{
			gettimeofday(&start, NULL);
			printf("%d %d is thinking\n", start.tv_usec, temp->id + 1);
			temp->status = 1;
			if (!check_death(temp))
			{
				pthread_detach();
				printdeath;
			}
		}
		if (temp->status == 1)
		{
			pick_fork(temp);
			if (!(i = check_death(temp)))
				temp->status = 0;
		}
		if (temp->status == 2)
		{
			gettimeofday(&start, NULL);
			printf("%d %d is sleeping\n", start.tv_usec, temp->id + 1);
			usleep(temp->time_to_sleep);
			i = check_death(temp);
			temp->status = 0;
		}
	}
	return (NULL);
}

// CREATE PARAM CHECK BEFORE START CODE	


// STATUS CODE 0 - WANTS TO EAT, DID NOT PRINT THAT IS THINKING
// STATUS CODE 1 - WANTS TO EAT, ALREADY PRINT THAT IS THINKING
// STATUS CODE 2 - IS EATING, READY TO SLEEP

static t_philo	*initialize_id(int argc, char **argv, int i, t_philo *id)
{
	t_philo	*temp;
	struct timeval 	start;

	gettimeofday(&start, NULL);
	temp = id;
	temp->phil_num = ft_atoi(argv[1]);
	temp->time_to_die = ft_atoi(argv[2]);
	temp->time_to_eat = ft_atoi(argv[3]);
	temp->time_to_sleep = ft_atoi(argv[4]);
	temp->last_eat = start.tv_usec;
	temp->id = i;
	if (argc == 6)
		temp->eat_count = ft_atoi(argv[5]);
	temp->status = 0;
	temp->detach = 1;
	return (temp);
}

// em caso de erro na criação da thread eu preciso terminar o processo.
int	create_threads(int argc, char **argv, int philonum, pthread_t	*philos)
{
	int				i;
	t_philo			*id;
	pthread_mutex_t *forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * philonum);
	if (!forks)
		return (malloc_error());
	while (i < philonum)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < philonum)
	{
		id =  malloc(sizeof(t_philo));
		if (!id)
			return (malloc_error());
		id = initialize_id(argc, argv, i, id);
		id->forks = forks;
		if (pthread_create(&philos[i], NULL, &routine, id))
			return (create_thread_error());
		i++;
	}
	join_threads(philonum, philos);
	i = 0;
	while (i < philonum)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	return (1);
}

void	join_threads(int philonum, pthread_t	*philos)
{
	int	i;

	i = 0;
	while(i < philonum)
	{
		if (philos->detach)
			pthread_join(philos[i], NULL);
		i++;
	}
}