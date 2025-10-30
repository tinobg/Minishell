/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:22:22 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:18:58 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_quotes(t_index *i_data, const char *s)
{
	i_data->malloc_size++;
	if (s[i_data->i++] == '\'')
	{
		while (s[i_data->i] && s[i_data->i++] != '\'')
			i_data->malloc_size++;
	}
	else
	{
		while (s[i_data->i] && s[i_data->i++] != '\"')
				i_data->malloc_size++;
	}
	i_data->malloc_size++;
}

static void	get_size(t_index *i_data, const char *s)
{
	i_data->malloc_size = 0;
	while (s[i_data->i] && s[i_data->i] != ' ')
	{
		if (s[i_data->i] == '\'' || s[i_data->i] == '\"')
			handle_quotes(i_data, s);
		if (s[i_data->i])
		{
			i_data->malloc_size++;
			i_data->i++;
		}
	}
	if (s[i_data->i])
		i_data->i++;
}

static size_t	ft_countstr(char const *s)
{
	t_index	i_data;
	size_t	counter;

	i_data.i = 0;
	counter = 0;
	while (s[i_data.i])
	{
		get_size(&i_data, s);
		if (i_data.malloc_size != 0)
			counter++;
	}
	return (counter);
}

static void	ft_split2(char **str, char const *s, size_t count)
{
	t_index	i_data;

	i_data.i = 0;
	i_data.j = 0;
	while (i_data.j < count)
	{
		get_size(&i_data, s);
		str[i_data.j] = (char *)malloc((i_data.malloc_size + 1) * sizeof(char));
		str[i_data.j][i_data.malloc_size] = '\0';
		if (str[i_data.j++] == NULL)
		{
			str = NULL;
			break ;
		}
	}
}

char	**parse_whitespace(char const *s)
{
	char	**str;
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_countstr(s);
	str = (char **)malloc((i + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	ft_split2(str, s, i);
	if (str == NULL)
		return (NULL);
	parse_split(s, str, i);
	return (str);
}
