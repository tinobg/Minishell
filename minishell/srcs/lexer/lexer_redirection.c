/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:29:34 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:07:15 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_quotes(t_index *i_data, const char *s)
{
	if (s[i_data->i++] == '\'')
	{
		while (s[i_data->i] && s[i_data->i] != '\'')
			i_data->i++;
	}
	else
	{
		while (s[i_data->i] && s[i_data->i] != '\"')
				i_data->i++;
	}
	if (s[i_data->i])
		i_data->i++;
}

static void	redirections_errors(const char *s, t_commands *cmds, \
							t_index *i_data)
{
	if (cmds->exit_value == 0 && s[i_data->i])
	{
		cmds->exit_value = 2;
		ft_putstr_fd("-minishell: syntax error near unexpected token `", \
		STDERR);
		while (s[i_data->i] && (s[i_data->i] == '&' || s[i_data->i] == '|' || \
			s[i_data->i] == '>' || s[i_data->i] == '<'))
			ft_putchar_fd(s[i_data->i++], STDERR);
		ft_putstr_fd("'\n", STDERR);
	}
	if (cmds->exit_value == 0 && !s[i_data->i])
	{
		cmds->exit_value = 2;
		ft_putstr_fd("-minishell: syntax error near unexpected token `", \
		STDERR);
		ft_putstr_fd("newline'\n", STDERR);
	}
}

static void	handle_redirection(const char *str, t_commands *cmds, \
			t_index *i_data)
{
	i_data->i++;
	if (str[i_data->i] && (str[i_data->i] == '<' || str[i_data->i] == '>'))
		i_data->i++;
	while (str[i_data->i] && str[i_data->i] == ' ')
		i_data->i++;
	if (str[i_data->i] && (str[i_data->i] == '&' || str[i_data->i] == '|') && \
		(str[i_data->i - 1] == '<' || \
		str[i_data->i - 1] == '>' || str[i_data->i - 1] == ' '))
		redirections_errors(str, cmds, i_data);
	if (str[i_data->i] && (str[i_data->i] == '<' || str[i_data->i] == '>') && \
		(str[i_data->i - 1] == '<' || str[i_data->i - 1] == '>' || \
		str[i_data->i - 1] == ' '))
		redirections_errors(str, cmds, i_data);
	if (!str[i_data->i])
		redirections_errors(str, cmds, i_data);
}

void	lexer_redirections(const char *str, t_commands *cmds)
{
	t_index	i_data;

	i_data.i = 0;
	while (str[i_data.i])
	{
		if (str[i_data.i] && (str[i_data.i] == '<' || str[i_data.i] == '>'))
			handle_redirection(str, cmds, &i_data);
		if (str[i_data.i] && (str[i_data.i] == '\'' || str[i_data.i] == '\"'))
			handle_quotes(&i_data, str);
		if (str[i_data.i])
			i_data.i++;
	}
}
