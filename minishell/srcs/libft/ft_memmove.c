/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:47:57 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 18:48:09 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memmove(void *des, void *src, size_t len)
{
	unsigned int	i;

	if (des == NULL || src == NULL)
		return (NULL);
	if (des < src)
	{
		i = 0;
		while (i < len)
		{
			((char *) des)[i] = ((char *) src)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			((char *) des)[i - 1] = ((char *) src)[i - 1];
			i--;
		}
	}
	return (des);
}
