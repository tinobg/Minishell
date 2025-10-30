/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjoves <brjoves@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:29:36 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 16:19:56 by brjoves          ###   ########.fr       */
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

static void	copy_quotes(char *s, char *new_str, t_tmp_index *data)
{
	new_str[data->o++] = s[data->i++];
	if (s[data->i - 1] == '\'')
	{
		while (s[data->i] && s[data->i] != '\'')
			new_str[data->o++] = s[data->i++];
	}
	else
	{
		while (s[data->i] && s[data->i] != '\"')
			new_str[data->o++] = s[data->i++];
	}
	new_str[data->o++] = s[data->i++];
}

static void	ft_strcpy2(char *s, char *new_str, t_tmp_index *data)
{
	data->o = 0;
	while (s[data->i])
	{
		while (s[data->i] && (s[data->i] != '<' && s[data->i] != '>'))
		{
			if (s[data->i] == '\'' || s[data->i] == '\"')
				copy_quotes(s, new_str, data);
			else
				new_str[data->o++] = s[data->i++];
		}
		while (s[data->i] && (s[data->i] == '<' || s[data->i] == '>' || \
				s[data->i] == ' ' ))
			data->i++;
		while (s[data->i] && s[data->i] != ' ')
		{
			if (s[data->i] == '\'' || s[data->i] == '\"')
				handle_quotes(data, s, s[data->i]);
			else
				data->i++;
		}
	}
}

void	add_arg_to_cmd(char *str, char *new_str)
{
	t_tmp_index	data;

	data.i = 0;
	data.j = 0;
	ft_strcpy2(str, new_str, &data);
}
