/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:40:47 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:28:04 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_quotes(t_index *i_data, char *s, int add_malloc, \
					char special_char)
{
	if (add_malloc == 1)
	{
		i_data->i++;
		while (s[i_data->i] && s[i_data->i++] != special_char)
			i_data->malloc_size++;
	}
	else
	{
		i_data->i++;
		while (s[i_data->i] && s[i_data->i++] != special_char)
			;
	}
}

static void	get_size(t_index *i_data, char *s)
{
	i_data->malloc_size = 0;
	while (s[i_data->i] && s[i_data->i] != '<' && s[i_data->i] != '>')
	{
		if (s[i_data->i] == '\'' || s[i_data->i] == '\"')
			handle_quotes(i_data, s, 0, s[i_data->i]);
		else
			i_data->i++;
	}
	while (s[i_data->i] && (s[i_data->i] == '<' || s[i_data->i] == '>' || \
			s[i_data->i] == ' ' ))
	{
		i_data->i++;
		i_data->malloc_size++;
	}
	while (s[i_data->i] && s[i_data->i] != ' ')
	{
		if (s[i_data->i] == '\'' || s[i_data->i] == '\"')
			handle_quotes(i_data, s, 1, s[i_data->i]);
		else
		{
			i_data->malloc_size++;
			i_data->i++;
		}
	}
}

static size_t	ft_countstr(char *s)
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

static void	ft_split2(char **str, char *s, size_t countc)
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

char	**parse_redirections(char *input)
{
	char	**str;
	size_t	i;

	if (!input)
		return (NULL);
	i = ft_countstr(input);
	str = (char **)malloc((i + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	ft_split2(str, input, i);
	if (str == NULL)
		return (NULL);
	parse_full_redirections(input, str, i);
	return (str);
}
