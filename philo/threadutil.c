/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadutil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san <sdos-san@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:22:27 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/25 18:38:33 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/*long long time_diff(t_shared *temp, struct timeval last_eat)
{
	struct timeval	start;
	long long		current_time;
	long long		last_eat_time;

	gettimeofday(&start, NULL);
	current_time = (start.tv_sec - temp->begin_time.tv_sec) * 1000;
	current_time =  current_time + (start.tv_usec - temp->begin_time.tv_usec) * 0.001;
	last_eat_time = (last_eat.tv_sec - temp->begin_time.tv_sec) * 1000;
	last_eat_time =  last_eat_time + (last_eat.tv_usec - temp->begin_time.tv_usec) * 0.001;
	return(current_time - last_eat_time);
}*/

void	my_print(t_philo	*temp, int code)
{
	pthread_mutex_lock(&temp->global->printf);
	if (code == 1)
		printf("%lld %d is thinking\n", gett_time(), temp->id + 1);
	else if (code == 2)
		printf("%lld %d pick up a fork\n", gett_time(), temp->id + 1);
	else if (code == 3)
		printf("%lld %d is eating\n", gett_time(), temp->id + 1);
	else if (code == 4)
		printf("%lld %d is sleeping\n", gett_time(), temp->id + 1);
	else if (code == 5)
		printf("%lld %d is DEAD! Press F to pay respects.\n", \
											gett_time(), temp->id + 1);
	pthread_mutex_unlock(&temp->global->printf);
}

struct timeval get_time(void)
{
	struct timeval start;

	gettimeofday(&start, NULL);
	return(start);
}


long long gett_time(void)
{
	
	struct 			timeval	start;
	long long		current_time;

	gettimeofday(&start, NULL);
	current_time = (start.tv_sec) * 1000;
	current_time =  current_time + (start.tv_usec) * 0.001;
	return(current_time);
}


/*long long	ft_get_time(t_philo	*philo)
{
	struct timeval	start;
	long long		current_time;

	gettimeofday(&start, NULL);
	current_time = (start.tv_sec - philo->global->begin_time.tv_sec) * 1000;
	current_time =  current_time + (start.tv_usec - philo->global->begin_time.tv_usec) * 0.001;
	return(current_time);
}*/