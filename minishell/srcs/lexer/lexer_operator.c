/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:33:49 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 16:43:08 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	operators_errors(const char *s, t_commands *cmds, \
							t_index *i_data)
{
	if (cmds->exit_value == 0 && s[i_data->i])
	{
		cmds->exit_value = 2;
		ft_putstr_fd("-minishell: syntax error near unexpected token `", \
		STDERR);
		while (s[i_data->i] && (s[i_data->i] == '&' || s[i_data->i] == '|'))
			ft_putchar_fd(s[i_data->i++], STDERR);
		ft_putstr_fd("'\n", STDERR);
	}
	if (cmds->exit_value == 0 && !s[i_data->i])
	{
		cmds->exit_value = error_msg(NULL, NULL, \
		"-minishell: syntax error: not expecting newline", 2);
	}
}

void	lexer_operators(const char *str, t_commands *cmds)
{
	t_index	i_data;

	i_data.i = 0;
	while (str[i_data.i] && str[i_data.i] == ' ')
			i_data.i++;
	if (str[i_data.i] == '&' || str[i_data.i] == '|')
		operators_errors(str, cmds, &i_data);
	else
	{
		while (str[i_data.i])
		{
			if (str[i_data.i] && (str[i_data.i] == '&' || str[i_data.i] == '|'))
			{
				i_data.i++;
				while (str[i_data.i] && str[i_data.i] == ' ')
					i_data.i++;
				if (!str[i_data.i])
					operators_errors(str, cmds, &i_data);
			}
			else
				i_data.i++;
		}
	}
}
