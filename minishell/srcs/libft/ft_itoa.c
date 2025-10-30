/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:13:36 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:35:21 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static long	is_negative(long nb)
{
	if (nb >= 0)
		return (0);
	else
		return (1);
}

static long	ft_modulotruc(long nb)
{
	long	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	char	*result;
	int		negative;
	int		digits;
	long	number;

	number = nb;
	negative = is_negative(number);
	if (negative == 1)
		number = number * -1;
	digits = ft_modulotruc(number);
	result = (char *) malloc(digits + negative + 1);
	if (result == NULL)
		return (NULL);
	if (negative == 1)
		result[0] = '-';
	result[digits + negative] = '\0';
	while (digits > 0)
	{
		result[(digits - 1) + negative] = (number % 10) + '0';
		number = number / 10;
		digits--;
	}
	return (result);
}
