/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_full_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:26:19 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:25:33 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

typedef struct s_tmp_index
{
	size_t	i;
	size_t	o;
	size_t	j;
}	t_tmp_index;

static void	handle_quotes(t_tmp_index *data, char *s, char special_char)
{
	data->i++;
	while (s[data->i] && s[data->i] != special_char)
		data->i++;
	data->i++;
}

static void	copy_quotes(char *s, char **str, t_tmp_index *data)
{
	data->i++;
	if (s[data->i - 1] == '\'')
	{
		while (s[data->i] && s[data->i] != '\'')
			str[data->j][data->o++] = s[data->i++];
	}
	else
	{
		while (s[data->i] && s[data->i] != '\"')
			str[data->j][data->o++] = s[data->i++];
	}
	data->i++;
}

static void	ft_strcpy2(char *s, char **str, t_tmp_index *data)
{
	data->o = 0;
	while (s[data->i] && (s[data->i] != '<' && s[data->i] != '>'))
	{
		if (s[data->i] == '\'' || s[data->i] == '\"')
			handle_quotes(data, s, s[data->i]);
		else
			data->i++;
	}
	while (s[data->i] && (s[data->i] == '<' || s[data->i] == '>' || \
			s[data->i] == ' ' ))
		str[data->j][data->o++] = s[data->i++];
	while (s[data->i] && s[data->i] != ' ')
	{
		if (s[data->i] == '\'' || s[data->i] == '\"')
			copy_quotes(s, str, data);
		else
			str[data->j][data->o++] = s[data->i++];
	}
}

void	parse_full_redirections(char *input, char **str, size_t i)
{
	t_tmp_index	data;

	data.i = 0;
	data.j = 0;
	while (data.j < i)
	{
		ft_strcpy2(input, str, &data);
		data.j++;
	}
	str[data.j] = NULL;
}
