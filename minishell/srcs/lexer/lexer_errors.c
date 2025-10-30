/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:00:27 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 16:43:32 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_errors(t_index *i_data, const char *str, t_commands *cmds)
{
	if (!str[i_data->i] && (str[i_data->i - 1] == '|'
			|| str[i_data->i - 1] == '&'))
		cmds->exit_value = error_msg(NULL, NULL, \
		"-minishell: syntax error not expecting newline", 2);
	while (str[i_data->i] && (str[i_data->i] == '|' || str[i_data->i] == '&' \
		|| str[i_data->i] == ' '))
	{
		if ((str[i_data->i] == '|' || str[i_data->i] == '&')
			&& cmds->exit_value == 0)
		{
			cmds->exit_value = 2;
			ft_putstr_fd("-minishell: syntax error near unexpected token `", \
				STDERR);
			while (str[i_data->i] && (str[i_data->i] == '|'
					|| str[i_data->i] == '&'))
				ft_putchar_fd(str[i_data->i++], STDERR);
			ft_putstr_fd("'\n", STDERR);
		}
		i_data->i++;
		if (!str[i_data->i] && cmds->exit_value == 0)
			cmds->exit_value = error_msg(NULL, NULL, \
				"-minishell: syntax error: not expecting newline", 2);
	}
}

void	quotes_error(t_index *i_data, const char *str, t_commands *cmds)
{
	if (!str[i_data->i] && cmds->exit_value == 0)
	{
		cmds->exit_value = 2;
		ft_putstr_fd("-minishell: syntax error: unclosed quotes\n", \
		STDERR);
	}
}
