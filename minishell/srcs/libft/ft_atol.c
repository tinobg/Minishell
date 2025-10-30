/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 00:13:01 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/26 17:16:43 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	toolong(int sign, unsigned long long nb, bool *error)
{
	if ((sign == 1 && nb > LONG_MAX)
		|| (sign == -1 && nb > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

int	ft_atol(const char *str, bool *error)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nb = (nb * 10) + (str[i] - '0');
		if (toolong(sign, nb, error))
			break ;
		i++;
	}
	return (nb * sign);
}
