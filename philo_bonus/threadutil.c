/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadutil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:22:27 by sdos-san          #+#    #+#             */
/*   Updated: 2022/12/01 13:13:57 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	my_print(t_philo	*temp, int code)
{
	sem_wait(temp->print);
	if (code == 1)
		printf("%lld %d is thinking\n", \
					ft_return_time(temp->begin_time), temp->id + 1);
	else if (code == 2)
		printf("%lld %d pick up a fork\n", \
					ft_return_time(temp->begin_time), temp->id + 1);
	else if (code == 3)
		printf("%lld %d is eating\n", \
					ft_return_time(temp->begin_time), temp->id + 1);
	else if (code == 4)
		printf("%lld %d is sleeping\n", \
					ft_return_time(temp->begin_time), temp->id + 1);
	else if (code == 5)
		printf("%lld %d has finished eating\n", \
					ft_return_time(temp->begin_time), temp->id + 1);
	sem_post(temp->print);
}

long long	get_begin_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec) * 1000 + (start.tv_usec) * 0.001);
}

long long	ft_return_time(long long begin_time)
{
	struct timeval	start;
	long long		current_time;

	gettimeofday(&start, NULL);
	current_time = (start.tv_sec) * 1000;
	current_time = current_time + (start.tv_usec) * 0.001;
	return (current_time - begin_time);
}
