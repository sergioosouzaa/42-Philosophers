/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:37:56 by sdos-san          #+#    #+#             */
/*   Updated: 2022/12/01 13:30:54 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	my_sleep(t_philo *philo, unsigned int militime)
{
	philo->time = ft_return_time(philo->begin_time);
	while (ft_return_time(philo->begin_time) - philo->time < militime)
		usleep(100);
}

void	pick_forks(t_philo *philo)
{

	philo->fork_num = 0;
	while (philo->fork_num < 2)
	{
		sem_wait(philo->forks);
		my_print(philo, 2);
		philo->fork_num++;
	}
	return ;
}

void	*life(void *id)
{
	t_philo	*temp;
	int 	i;

	temp = (t_philo *)id;
	i  = 0;
	while (temp->eat_count != (int)temp->eat_max)
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
