/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdos-san < sdos-san@student.42.rio >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:37:03 by sdos-san          #+#    #+#             */
/*   Updated: 2022/11/09 13:37:28 by sdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_iswhitespace(int ch)
{
	return ((ch >= 9 && ch <= 13) || ch == 32);
}

static int	ft_isdigit(int ch)
{
	return (ch >= 48 && ch <= 57);
}

unsigned int	ft_atoi(const char *str)
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