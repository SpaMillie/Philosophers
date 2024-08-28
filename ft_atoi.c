/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:47:55 by mspasic           #+#    #+#             */
/*   Updated: 2024/08/28 18:14:38 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"


static int	ft_sign(char c)
{
	if (c == '-')
		return (-1);
	if (c == '+')
		return (1);
	return (0);
}

static int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int				sign;
	int				i;
	unsigned long	num;

	i = 0;
	num = 0;
	sign = ft_sign(str[i]);
	if (sign != 0)
		i++;
	while (ft_isnum(str[i]) == 1)
	{
		num = num * 10 + (str[i++] - '0');
		if (num > 9223372036854775807 || num > 9223372036854775808ULL)
			return (-1);
	}
	if (sign != 0 && num != 0)
		return (sign * num);
	if (num > 2147483647)
		num = -1;
	return (num);
}
