/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:41:29 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:09:35 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_quotes(t_index *i_data, const char *str, t_commands *cmds)
{
	i_data->malloc_size++;
	if (str[i_data->i++] == '\'')
	{
		while (str[i_data->i] && str[i_data->i++] != '\'')
			i_data->malloc_size++;
	}
	else
	{
		while (str[i_data->i] && str[i_data->i++] != '\"')
				i_data->malloc_size++;
	}
	if (!str[i_data->i] && str[i_data->i - 1] != '\"'
		&& str[i_data->i - 1] != '\'')
		quotes_error(i_data, str, cmds);
	else
		i_data->malloc_size++;
}

static void	get_size(t_index *i_data, const char *str, t_commands *cmds)
{
	i_data->malloc_size = 0;
	while (str[i_data->i] && str[i_data->i] != '&' && str[i_data->i] != '|')
	{
		if (str[i_data->i] == '\'' || str[i_data->i] == '\"')
			handle_quotes(i_data, str, cmds);
		if (str[i_data->i])
			i_data->malloc_size++;
		if (str[i_data->i])
			i_data->i++;
	}
	if (str[i_data->i] == '&' && str[i_data->i + 1] == '&')
		i_data->i = i_data->i + 2;
	if (str[i_data->i] == '|' && str[i_data->i + 1] == '|')
		i_data->i = i_data->i + 2;
	if (str[i_data->i] == '|' && str[i_data->i - 1] != '|'
		&& str[i_data->i - 1] != '&')
		i_data->i++;
	handle_errors(i_data, str, cmds);
}

static void	ft_split2(char **s1, char const *s2, size_t count, t_commands *cmds)
{
	t_index	i_data;

	i_data.i = 0;
	i_data.j = 0;
	while (i_data.j < count)
	{
		get_size(&i_data, s2, cmds);
		s1[i_data.j] = (char *)malloc((i_data.malloc_size + 1) * sizeof(char));
		s1[i_data.j][i_data.malloc_size] = '\0';
		if (s1[i_data.j++] == NULL)
		{
			s1 = NULL;
			break ;
		}
	}
}

static size_t	ft_countstr(char const *str, t_commands *cmds)
{
	t_index	i_data;
	size_t	counter;

	i_data.i = 0;
	counter = 0;
	while (str[i_data.i])
	{
		get_size(&i_data, str, cmds);
		if (i_data.malloc_size != 0)
			counter++;
	}
	return (counter);
}

char	**tokenize_input(char const *input, t_commands *cmds)
{
	char	**str;
	size_t	i;

	if (!input)
		return (NULL);
	lexer_redirections(input, cmds);
	lexer_operators(input, cmds);
	if (cmds->exit_value != 0)
		return (NULL);
	i = ft_countstr(input, cmds);
	lexer_parentheses(input, cmds);
	if (cmds->exit_value != 0)
		return (NULL);
	str = (char **)malloc((i + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	ft_split2(str, input, i, cmds);
	if (str == NULL)
		return (NULL);
	add_token(input, str, i);
	return (str);
}
