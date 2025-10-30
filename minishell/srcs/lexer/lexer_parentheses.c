/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:48:17 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 16:43:40 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_quotes(t_index *i_data, const char *str)
{
	if (str[i_data->i++] == '\'')
	{
		while (str[i_data->i] && str[i_data->i] != '\'')
			i_data->i++;
	}
	else
	{
		while (str[i_data->i] && str[i_data->i] != '\"')
				i_data->i++;
	}
	if (str[i_data->i])
		i_data->i++;
}

static void	parentheses_errors(const char *s, t_commands *cmds, \
							t_index *i_data)
{
	if (s[i_data->i] == '(' || s[i_data->i] == ')')
	{
		i_data->i++;
		while (s[i_data->i] && s[i_data->i] == ' ')
			i_data->i++;
	}
	if (cmds->exit_value == 0 && s[i_data->i])
	{
		cmds->exit_value = 2;
		ft_putstr_fd("-minishell: syntax error near unexpected token `", \
		STDERR);
		while (s[i_data->i])
			ft_putchar_fd(s[i_data->i++], STDERR);
		ft_putstr_fd("'\n", STDERR);
	}
	if (cmds->exit_value == 0 && !s[i_data->i] && s[i_data->i - 1] != ')')
	{
		cmds->exit_value = error_msg(NULL, NULL, \
		"-minishell: syntax error not expecting newline", 2);
	}
}

static void	handle_parentheses(const char *s, t_commands *cmds, t_index \
			*i_data)
{
	int	i;

	i = 0;
	i_data->i++;
	while (s[i_data->i] && s[i_data->i] == ' ')
		i_data->i++;
	if (s[i_data->i] && s[i_data->i] == ')')
		parentheses_errors(s, cmds, i_data);
	while (s[i_data->i] && s[i_data->i] != ')')
	{
		if (s[i_data->i] == '\'' || s[i_data->i] == '\"')
			handle_quotes(i_data, s);
		if (s[i_data->i++] == '(')
			handle_parentheses(s, cmds, i_data);
	}
	if (!s[i_data->i] && s[i_data->i - 1] != ')')
		parentheses_errors(s, cmds, i_data);
	while (s[i_data->i + i] && (s[i_data->i + i] != '&' && s[i_data->i + i] \
			!= '|'))
		i++;
	if (!s[i_data->i + i])
		parentheses_errors(s, cmds, i_data);
	else
		i_data->i++;
}

void	lexer_parentheses(const char *str, t_commands *cmds)
{
	t_index	i_data;

	i_data.i = 0;
	while (str[i_data.i])
	{
		while (str[i_data.i] && str[i_data.i] == ' ')
			i_data.i++;
		if (str[i_data.i] == ')')
			parentheses_errors(str, cmds, &i_data);
		if (str[i_data.i] == '(')
			handle_parentheses(str, cmds, &i_data);
		while (str[i_data.i] && str[i_data.i] != '&' && str[i_data.i] != '|')
		{
			if (str[i_data.i] == ')' || str[i_data.i] == '(')
				parentheses_errors(str, cmds, &i_data);
			if (str[i_data.i] == '\'' || str[i_data.i] == '\"')
				handle_quotes(&i_data, str);
			if (str[i_data.i])
				i_data.i++;
		}
		if (str[i_data.i] == '&' || str[i_data.i] == '|')
			i_data.i++;
	}
}
