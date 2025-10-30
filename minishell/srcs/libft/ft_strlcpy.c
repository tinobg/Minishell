/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:26:32 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:36:08 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t			src_len;
	unsigned int	i;

	i = 0;
	if (!dst || !src)
		return (0);
	src_len = ft_strlen(src);
	if (len <= 0)
		return (src_len);
	while (src[i] && i < (len - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
