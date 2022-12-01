/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:37:03 by sdos-san          #+#    #+#             */
/*   Updated: 2022/12/01 11:04:33 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_iswhitespace(int ch)
{
	return ((ch >= 9 && ch <= 13) || ch == 32);
}

int	ft_isdigit(int ch)
{
	return (ch >= 48 && ch <= 57);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

long int	ft_atoi(const char *str)
{
	unsigned int	pos;
	long int		output;

	output = 0;
	pos = 0;
	while (ft_iswhitespace(*(str + pos)))
		pos++;
	if (*(str + pos) == '-')
		return (0);
	else if (*(str + pos) == '+')
		pos++;
	while (*(str + pos) && ft_isdigit(*(str + pos)))
	{
		output = (output * 10) + (*(str + pos) - '0');
		pos++;
	}
	return (output);
}
