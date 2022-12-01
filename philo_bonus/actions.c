/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:37:29 by sdos-san          #+#    #+#             */
/*   Updated: 2022/12/01 13:29:56 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	philo_sleep(t_philo	*philo)
{
	my_print(philo, 4);
	my_sleep(philo, philo->time_to_sleep);
	philo->status = 0;
}

void	philo_think(t_philo	*philo)
{
	my_print(philo, 1);
	philo->status = 1;
}

void	philo_eat(t_philo	*philo)
{	
	my_print(philo, 3);
	philo->eaten_times = ft_return_time(philo->begin_time);
	philo->eat_count++;
	my_sleep(philo, philo->time_to_eat);
	while (philo->fork_num > 0)
	{
		sem_post(philo->forks);
		philo->fork_num--;
	}
	if (philo->eat_count == (int)philo->eat_max)
	{
		my_print(philo, 5);
		philo->status = 0;
		return ;
	}
	philo->status = 2;
}

void	*finish_them(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (ft_return_time(philo->begin_time) - philo->eaten_times > \
														philo->time_to_die)
		{
			if (!(philo->eat_count == (int)philo->eat_max))
			{
				printf("%lld %d is DEAD! Press F to pay respects.\n", \
								ft_return_time(philo->begin_time), philo->id);
				sem_post(philo->die);
				return (NULL);
			}
		}
	}
}
