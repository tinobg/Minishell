/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:24:05 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/26 00:02:33 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	int		cmp;

	if (n == 0)
		return (0);
	i = 0;
	while ((str1[i] == str2[i]) && (str1[i] != '\0') && (str2[i] != '\0')
		&& (i < (n - 1)))
		i++;
	cmp = (str1[i] - str2[i]);
	return (cmp);
}
