/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san <sdos-san@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:37:56 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/25 18:35:41 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_sleep(t_philo *philo, unsigned int militime)
{
	philo->time = gett_time();
	philo->microtime = militime * 1000;
	while (gett_time() - philo->time < militime * 1000)
	{
		usleep(100);
		if (philo->global->pestilence)
			return ;
	}
}

void	pick_forks(t_philo *philo)
{
	philo->first = (philo->id + 1) % philo->global->phil_num;
	philo->second = philo->id;
	if (philo->id % 2 == 0)
	{
		philo->first = philo->id;
		philo->second = (philo->id + 1) % philo->global->phil_num;
	}
	if (!philo->global->pestilence)
		return;
	pthread_mutex_lock(&philo->global->forks[philo->first]);
	/*if (philo->first == philo->second)
	 ....*/
	my_print(philo, 2);
	if (!philo->global->pestilence)
	{
		pthread_mutex_unlock(&philo->global->forks[philo->first]);
		return;
	}
	pthread_mutex_lock(&philo->global->forks[philo->second]);
	my_print(philo, 2);
}

/*void	philo_sleep(t_philo	*philo)
{
	my_print(philo, 4);
	my_sleep(philo, philo->global->time_to_sleep);
	philo->status = 0;
}*/

void	philo_eat(t_philo	*philo)
{	
	int	first;
	int second;

	first = (philo->id + 1) % philo->global->phil_num;
	second = philo->id;
	if (philo->id % 2 == 0)
	{
		first = philo->id;
		second = (philo->id + 1) % philo->global->phil_num;
	}
	my_print(philo, 3);
	philo->global->eaten_times[philo->id] =  gett_time();
	philo->eat_count++;
	my_sleep(philo, philo->global->time_to_eat);
	pthread_mutex_unlock(&philo->global->forks[second]);
	pthread_mutex_unlock(&philo->global->forks[first]);
	if (philo->eat_count == philo->global->eat_max && philo->global->eat_max > 0)
		return ;
	if (philo->global->pestilence)
	{
		my_print(philo, 4);
		my_sleep(philo, philo->global->time_to_sleep);
	}
	philo->status = 0;
}

void	philo_think(t_philo	*philo)
{
	my_print(philo, 1);
	philo->status = 1;
}

void	*kill(void *data)
{
	t_shared	*temp;
	int			i;
	temp = (t_shared *)data;

	i = 0;
	while (1)
	{
		if (gett_time() - temp->eaten_times[i] > temp->time_to_die)
		{
			temp->pestilence = 0;
			return (NULL);
		}
		i++;
		if (i == (int)temp->phil_num)
			i = 0;
	}
}

void	*life(void *id)
{
	t_philo	*temp;

	temp = (t_philo *)id;
	while(temp->global->pestilence && !(temp->eat_count == temp->global->eat_max))
	{
		if (temp->status == 0)
			philo_think(temp);
	 	if (temp->status == 1)
	 	{
			pick_forks(temp);
			philo_eat(temp);
	 	}
	}
	return (NULL);
}





