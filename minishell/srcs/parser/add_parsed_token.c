/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_parsed_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:15:31 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 14:28:07 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

typedef struct s_tmp_index
{
	size_t	i;
	size_t	o;
	size_t	j;
}	t_tmp_index;

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
	while (s[data->i] && (s[data->i] == ' ' || s[data->i] == '('))
		data->i++;
	while (s[data->i] && s[data->i] != ' ')
	{
		if (s[data->i] == '\'' || s[data->i] == '\"')
			copy_quotes(s, str, data);
		else
		{
			if (s[data->i] == ')')
				data->i++;
			else
				str[data->j][data->o++] = s[data->i++];
		}
	}
}

void	add_parsed_token(char *s, char **str, size_t len)
{
	t_tmp_index	data;

	data.i = 0;
	data.j = 0;
	while (data.j < len)
	{
		ft_strcpy2(s, str, &data);
		data.j++;
	}
	str[data.j] = NULL;
}
