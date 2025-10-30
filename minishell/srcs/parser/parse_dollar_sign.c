/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:01:03 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/04 17:07:25 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_char(char c)
{
	if (c != '?')
		return (ft_isalnum(c) || c == '_');
	else
		return (1);
}

static void	handle_dollar(t_index *i_data, t_commands *cmds, \
					int num_cmd, t_data *data)
{
	char	*tmp;

	tmp = parse_env(i_data, cmds->cmds[num_cmd], data);
	free(cmds->cmds[num_cmd]);
	cmds->cmds[num_cmd] = (char *)malloc(ft_strlen(tmp) * \
						sizeof(char) + 1);
	cmds->cmds[num_cmd][ft_strlen(tmp)] = '\0';
	ft_strlcpy(cmds->cmds[num_cmd], tmp, ft_strlen(tmp) + 1);
	free(tmp);
}

static void	handle_quotes(t_index *aux, t_commands *cmds, \
					int n, t_data *data)
{
	if (cmds->cmds[n][aux->i++] == '\'')
		while (cmds->cmds[n][aux->i] != '\'')
			aux->i++;
	else
	{
		while (cmds->cmds[n][aux->i] != '\"')
		{
			if (cmds->cmds[n][aux->i] == '$' && cmds->cmds[n][aux->i + 1]
				&& check_char(cmds->cmds[n][aux->i + 1]))
				handle_dollar(aux, cmds, n, data);
			else
				aux->i++;
		}
	}
}

void	parse_dollar_sign(t_data *data, t_commands *cmds, int n)
{
	t_index	aux;

	aux.i = 0;
	find_export_cmd(cmds, n);
	while (cmds->cmds[n][aux.i])
	{
		if (cmds->cmds[n][aux.i] == '$' && cmds->cmds[n][aux.i + 1]
			&& check_char(cmds->cmds[n][aux.i + 1]))
			handle_dollar(&aux, cmds, n, data);
		if (cmds->cmds[n][aux.i] == '\'' || \
			cmds->cmds[n][aux.i] == '\"')
			handle_quotes(&aux, cmds, n, data);
		if (cmds->cmds[n][aux.i] == '$')
		{
			if (cmds->cmds[n][aux.i + 1] &&
				!check_char(cmds->cmds[n][aux.i + 1]))
				aux.i++;
			if (!cmds->cmds[n][aux.i + 1])
				aux.i++;
		}
		else if (cmds->cmds[n][aux.i] && cmds->cmds[n][aux.i] != '$')
			aux.i++;
	}
}
