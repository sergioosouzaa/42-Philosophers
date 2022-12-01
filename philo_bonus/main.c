/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:16:30 by sdos-san          #+#    #+#             */
/*   Updated: 2022/12/01 10:19:43 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/* Check if all the arguments are positive numbers */

int	check_arguments(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (j < (int)ft_strlen(argv[i]))
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 1)
			return (1);
		i++;
	}
	return (0);
}

/*Check parameters and then create the threads*/

int	main(int argc, char **argv)
{
	int			philonum;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of Arguments\n");
		return (0);
	}
	philonum = ft_atoi(argv[1]);
	if (check_arguments(argc, argv))
	{
		printf("Error: Invalid Arguments\n");
		return (0);
	}
	create_philo(argc, argv, philonum);
	return (0);
}
