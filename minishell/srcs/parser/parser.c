/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:47:06 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 13:52:09 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_quotes(t_index *i_data, char *str)
{
	if (str[i_data->i++] == '\'')
	{
		while (str[i_data->i] && str[i_data->i++] != '\'')
			i_data->malloc_size++;
	}
	else
	{
		while (str[i_data->i] && str[i_data->i++] != '\"')
				i_data->malloc_size++;
	}
}

static void	get_size(t_index *i_data, char *s)
{
	i_data->malloc_size = 0;
	while (s[i_data->i] && (s[i_data->i] == ' ' || s[i_data->i] == '('))
		i_data->i++;
	while (s[i_data->i] && s[i_data->i] != ' ')
	{
		if (s[i_data->i] == '\'' || s[i_data->i] == '\"')
			handle_quotes(i_data, s);
		else
		{
			if (s[i_data->i] == ')')
				i_data->i++;
			else
			{
				i_data->malloc_size++;
				i_data->i++;
			}
		}
	}
}

static size_t	ft_countstr(char *str)
{
	t_index	i_data;
	size_t	count;

	i_data.i = 0;
	count = 0;
	while (str[i_data.i])
	{
		get_size(&i_data, str);
		if (i_data.malloc_size != 0)
			count++;
	}
	return (count);
}

static void	splitstr(char **str, char *s, size_t countc)
{
	t_index	i_data;

	i_data.i = 0;
	i_data.j = 0;
	while (i_data.j < countc)
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

char	**parser(char *input)
{
	char	**str;
	size_t	i;

	if (!input)
		return (NULL);
	i = ft_countstr(input);
	str = (char **)malloc((i + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	splitstr(str, input, i);
	if (str == NULL)
		return (NULL);
	add_parsed_token(input, str, i);
	return (str);
}
