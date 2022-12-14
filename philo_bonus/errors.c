/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:42:29 by sdos-san          #+#    #+#             */
/*   Updated: 2022/12/01 10:19:11 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	malloc_error(void)
{
	printf("Error on malloc");
	return (0);
}

int	create_thread_error(void)
{
	printf("Error on initializing thread");
	return (0);
}

int	mutex_error(void)
{
	printf("Error on initializing mutex");
	return (0);
}
