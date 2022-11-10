/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:16:30 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/09 18:58:46 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	int			i;
	pthread_t	*philos;
	int			philonum;

	if (argc != 4 && argc != 5)
		return (0);
	philonum = ft_atoi(argv[1]);
	i = 0;
	philos = malloc(sizeof(pthread_t) * philonum);
	if (!philos)
		return (malloc_error());
	if (!create_threads(argc, argv, philonum, philos))
		return (0);
	return (0);
}