/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadutil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:22:27 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/23 14:22:34 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Vai virar o smartsleep

void	my_sleep(unsigned int	milisec)
{
	usleep(milisec * 1000);
}


// retornar o tamanho do tepo em relação o valor inicial

uint64_t	my_time(void)
{
	struct timeval 	time;
	uint64_t	mili_time;

	gettimeofday(&time, NULL);
	mili_time = (time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000);
	return (mili_time);
}

uint64_t time_diff(t_philo philo)
{
	struct timeval 	time;
	uint64_t	mili_time;

	gettimeofday(&time, NULL);
	mili_time = philo.last_eat.tv_sec * (uint64_t)1000 +  \
								philo.last_eat.tv_usec * 0.001;
	mili_time = time.tv_sec * (uint64_t)1000 + time.tv_usec * 0.001 - mili_time;
	return (mili_time);
}