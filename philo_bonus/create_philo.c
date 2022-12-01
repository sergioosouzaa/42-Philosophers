/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:27:27 by sdos-san          #+#    #+#             */
/*   Updated: 2022/12/01 14:28:10 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	open_semaphores(t_philo *philo)
{
	philo->forks = sem_open("forks", O_CREAT, 0644, philo->phil_num);
	philo->die = sem_open("die", O_CREAT, 0644, 0);
	philo->print = sem_open("print", O_CREAT, 0644, 1);
}

void	close_semaphores(t_philo *philo)
{
	sem_close(philo->print);
	sem_unlink("print");
	sem_close(philo->die);
	sem_unlink("forks");
	sem_close(philo->forks);
	sem_unlink("die");
}
/* Create the threads, one thread for each philosopher
   This function also initialize the values */

int	create_philo(int argc, char **argv, int philonum)
{
	int			i;
	t_philo		philo;
	pthread_t	assasin;
	int			*pids;

	i = 0;
	pids = malloc(sizeof(int) * philonum);
	while (i < philonum)
	{
		philo.pid = fork();
		if (philo.pid)
			pids[i] = philo.pid;
		if (!philo.pid)
			break ;
		i++;
	}
	if (!philo.pid)
	{
		initialize_id(&philo, argc, argv, i);
		pthread_create(&assasin, NULL, &finish_them, &philo);
		pthread_detach(assasin);
		life(&philo);
	}
	if (philo.pid)
	{
		sem_wait(philo.die);
		while (i < (int)philo.phil_num)
		{
			kill(pids[i], SIGKILL);
			i++;
		}
		free(pids);
	}
	return (0);
}

/* Initialize the shared struct between the philosphers */
/* STATUS CODE 0 - WANTS TO EAT, DID NOT PRINT THAT IS THINKING */
/* STATUS CODE 1 - WANTS TO EAT, ALREADY PRINT THAT IS THINKING */
/* STATUS CODE 2 - IS EATING, READY TO SLEEP */

void	initialize_id(t_philo *philo, int argc, char **argv, int id)
{
	philo->phil_num = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->begin_time = get_begin_time();
	philo->eat_max = -1;
	philo->eaten_times = 0;
	philo->eat_count = 0;
	philo->id = id;
	philo->status = 0;
	if (argc == 6)
		philo->eat_max = ft_atoi(argv[5]);
}
