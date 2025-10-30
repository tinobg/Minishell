/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:25:18 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/23 18:25:25 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	is_safe(size_t nmemb, size_t size)
{
	size_t	size_max;

	size_max = LONG_MAX;
	if (!nmemb || !size)
		return (0);
	if (nmemb > size_max / size || size > size_max / nmemb)
		return (LONG_MAX);
	return (nmemb * size);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*str;

	str = malloc(is_safe(nmemb, size));
	if (!str)
		return (0);
	ft_memset(str, 0, is_safe(nmemb, size));
	return (str);
}
