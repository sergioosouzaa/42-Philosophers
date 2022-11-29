/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:37:56 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/29 14:29:18 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_sleep(t_philo *philo, unsigned int militime)
{
	philo->time = ft_return_time(philo->global->begin_time);
	while (ft_return_time(philo->global->begin_time) - philo->time < militime)
	{
		usleep(100);
		if (!philo->global->pestilence)
			return ;
	}
}

void	pick_forks(t_philo *philo)
{
	if (!philo->global->pestilence)
		return ;
	pthread_mutex_lock(&philo->global->forks[philo->first]);
	my_print(philo, 2);
	if (philo->first == philo->second)
	{
		while (philo->global->pestilence)
			philo->second = philo->second++;
		pthread_mutex_unlock(&philo->global->forks[philo->first]);
		return ;
	}
	if (!philo->global->pestilence)
	{
		pthread_mutex_unlock(&philo->global->forks[philo->first]);
		return ;
	}
	pthread_mutex_lock(&philo->global->forks[philo->second]);
	my_print(philo, 2);
}

void	*life(void *id)
{
	t_philo	*temp;

	temp = (t_philo *)id;
	while (temp->global->pestilence && temp->global->eat_count[temp->id] \
								!= (int)temp->global->eat_max)
	{
		if (temp->status == 0)
			philo_think(temp);
		if (temp->status == 1)
		{
			pick_forks(temp);
			philo_eat(temp);
		}
		if (temp->status == 2)
		{
			philo_sleep(temp);
			temp->status = 0;
		}
	}
	return (NULL);
}
