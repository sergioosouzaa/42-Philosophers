/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:37:29 by sdos-san          #+#    #+#             */
/*   Updated: 2022/12/01 11:02:31 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_sleep(t_philo	*philo)
{
	my_print(philo, 4);
	my_sleep(philo, philo->global->time_to_sleep);
	philo->status = 0;
}

void	philo_think(t_philo	*philo)
{
	my_print(philo, 1);
	philo->status = 1;
}

void	philo_eat(t_philo	*philo)
{	
	if (!philo->global->pestilence)
	{
		pthread_mutex_unlock(&philo->global->forks[philo->second]);
		pthread_mutex_unlock(&philo->global->forks[philo->first]);
		return ;
	}
	my_print(philo, 3);
	philo->global->eaten_times[philo->id] = \
								ft_return_time(philo->global->begin_time);
	philo->global->eat_count[philo->id]++;
	my_sleep(philo, philo->global->time_to_eat);
	pthread_mutex_unlock(&philo->global->forks[philo->second]);
	pthread_mutex_unlock(&philo->global->forks[philo->first]);
	if (philo->global->eat_count[philo->id] == (int)philo->global->eat_max)
	{
		my_print(philo, 5);
		philo->status = 0;
		return ;
	}
	philo->status = 2;
}

int	check_eat(t_shared *temp)
{
	int	i;

	i = 0;
	while (i < (int)temp->phil_num)
	{
		if (temp->eat_count[i] != (int)temp->eat_max)
			return (0);
		i++;
	}
	return (1);
}

void	*finish_them(void *data)
{
	t_shared	*temp;
	int			i;

	temp = (t_shared *)data;
	i = 0;
	while (1)
	{
		if (ft_return_time(temp->begin_time) - temp->eaten_times[i] > \
														temp->time_to_die)
		{
			if (!(temp->eat_count[i] == (int)temp->eat_max))
			{
				temp->pestilence = 0;
				printf("%lld %d is DEAD! Press F to pay respects.\n", \
								ft_return_time(temp->begin_time), i + 1);
				return (NULL);
			}
		}
		i = (i + 1) % temp->phil_num;
		if (check_eat(temp))
			return (NULL);
	}
}
