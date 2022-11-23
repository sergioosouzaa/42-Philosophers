/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:37:56 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/23 16:53:55 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	check_death(t_philo	*philo, int *i)
// {
// 	pthread_mutex_lock(&philo->death);
// 	if (time_diff(*philo) > (uint64_t)philo->time_to_die)
// 	{
// 		printf("%lld HHUNGRY TTIME\n", time_diff(*philo));
// 		printf("%f last ead \n %lld time", philo->last_eat.tv_sec * 1000 + philo->last_eat.tv_usec * 0.001, my_time());
// 		printf("%f \n",  my_time() - philo->last_eat.tv_sec * 1000 + philo->last_eat.tv_usec * 0.001);
// 		printf("%d DIED!!!!!\n", philo->id + 1);
// 		*i = 1;
// 		pthread_mutex_unlock(&philo->death);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(&philo->death);
// 	return (1);
// }
// void	print_pick_fork(int id)
// {
// 	printf("%lld %d pick up a fork\n", my_time(), id + 1);
// }

// void	eating(t_philo	*philo)
// {
// 	philo->eat_count = philo->eat_count + 1;
// 	printf("%lld %d is eating\n", my_time(), philo->id + 1);
// 	philo->status = 2;
// 	my_sleep(philo->time_to_eat);
// 	// philo->last_eat = get_time();
// }


// void	pick_forks(t_philo	*philo, int *i)
// {
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(&philo->forks[(philo->id)]);
// 		print_pick_fork(philo->id);
// 		pthread_mutex_lock(&philo->forks[(philo->id + 1) % philo->phil_num]);
// 		print_pick_fork(philo->id);
// 		if (!check_death(philo, i) || *i)
// 		{
// 			pthread_mutex_unlock(&philo->forks[(philo->id + 1) % philo->phil_num]);
// 			pthread_mutex_unlock(&philo->forks[(philo->id)]);
// 			return ;
// 		}
// 		eating(philo);
// 		pthread_mutex_unlock(&philo->forks[(philo->id + 1) % philo->phil_num]);
// 		pthread_mutex_unlock(&philo->forks[(philo->id)]);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&philo->forks[(philo->id + 1) % philo->phil_num]);
// 		print_pick_fork(philo->id);
// 		pthread_mutex_lock(&philo->forks[(philo->id)]);
// 		print_pick_fork(philo->id);
// 		eating(philo);
// 		pthread_mutex_unlock(&philo->forks[(philo->id)]);
// 		pthread_mutex_unlock(&philo->forks[(philo->id + 1) % philo->phil_num]);
// 	}
// }


// void	think(t_philo	*philo, int *i)
// {
// 	if (!check_death(philo, i) || *i)
// 	{
// 		philo->status = 0;
// 		return ;
// 	}	
// 	printf("%lld %d is thinking\n", my_time(), philo->id + 1);
// 	philo->status = 1;
// 	if (!check_death(philo, i) || *i)
// 	{
// 		philo->status = 0;
// 		return ;
// 	}	
// }

// void	sleeping(t_philo	*philo, int *i)
// {
// 	if (!check_death(philo, i) || *i)
// 	{
// 		philo->status = 0;
// 		return ;
// 	}	
// 	printf("%lld %d is sleeping\n", my_time(), philo->id + 1);
// 	my_sleep(philo->time_to_sleep);
// 	if (!check_death(philo, i) || *i)
// 	{
// 		philo->status = 0;
// 		return ;
// 	}	
// 	philo->status = 0;
// }

void	*life(void *id)
{
	// t_philo			*temp;
	// int		i;

	// temp = (t_philo *)id;
	// i = 0;
	// while(!i)
	// {
	// 	if (temp->status == 0)
	// 		think(temp, &i);
	// 	if (temp->status == 1)
	// 	{
	// 		if (!check_death(temp, &i) || i)
	// 			return (NULL);
	// 		pick_forks(temp, &i);
	// 		if (!check_death(temp, &i) || i)
	// 			return (NULL);
	// 	}
	// 	if (temp->status == 2)
	// 		sleeping(temp, &i);
	// }
	(void)id;
	printf("its over\n");
	return (NULL);
}





