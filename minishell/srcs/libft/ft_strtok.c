/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:30:09 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/23 18:26:22 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strpbrk(const char *str, const char *accept)
{
	const char	*p;

	p = accept;
	while (*str != '\0')
	{
		while (*p != '\0')
		{
			if (*str == *p)
				return ((char *)str);
			p++;
		}
		str++;
	}
	return (NULL);
}

size_t	ft_strspn(const char *str, const char *accept)
{
	size_t		i;
	const char	*a;

	i = 0;
	a = accept;
	while (*str != '\0')
	{
		while (*a != '\0')
		{
			if (*str == *a)
				break ;
			a++;
		}
		if (*a == '\0')
			return (i);
		else
			i++;
	}
	return (i);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*token;

	if (str == NULL)
	{
		str = last;
		if (str == NULL)
			return (NULL);
	}
	str += ft_strspn(str, delim);
	if (*str == '\0')
	{
		last = NULL;
		return (NULL);
	}
	token = str;
	str = ft_strpbrk(token, delim);
	if (str)
	{
		*str = '\0';
		last = str + 1;
	}
	else
		last = NULL;
	return (token);
}
