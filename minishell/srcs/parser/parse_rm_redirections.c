/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rm_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:54:18 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 13:58:02 by jubaldo          ###   ########.fr       */
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
			count = count + i_data.malloc_size;
	}
	return (count);
}

char	*rm_redirections(char *str)
{
	char	*new_str;
	size_t	i;

	if (!str)
		return (NULL);
	i = ft_countstr(str);
	new_str = (char *)ft_calloc((ft_strlen(str) - i) + 1, sizeof(char *));
	new_str[ft_strlen(str) - i] = '\0';
	if (!new_str)
		return (NULL);
	add_arg_to_cmd(str, new_str);
	return (new_str);
}
