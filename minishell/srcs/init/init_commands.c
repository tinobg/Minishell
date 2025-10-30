/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:39:56 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:02:33 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_operators(t_data *data, t_commands *cmds, size_t *o, \
			size_t *i)
{
	if (data->user_input[*i] == '&' || data->user_input[*i + 1] == '&')
		cmds->operators[*o] = AND;
	if (data->user_input[*i] == '|' && data->user_input[*i + 1] == '|')
		cmds->operators[*o] = OR;
	if (data->user_input[*i] == '|' && data->user_input[*i + 1] != '|')
		cmds->operators[*o] = PIPE;
	*o = *o + 1;
	*i = *i + 1;
	if (data->user_input[*i] == '|' || data->user_input[*i] == '&')
		*i = *i + 1;
}

static void	get_operators(t_data *data, t_commands *cmds)
{
	size_t	i;
	size_t	o;
	char	spec_char;

	i = 0;
	o = 0;
	cmds->operators = ft_calloc(cmds->num_cmds, sizeof(int));
	while (data->user_input[i])
	{
		if (data->user_input[i] == '\'' || data->user_input[i] == '\"')
		{
			spec_char = data->user_input[i++];
			while (data->user_input[i] && data->user_input[i] != spec_char)
				i++;
		}
		if (data->user_input[i] == '&' || data->user_input[i] == '|')
			handle_operators(data, cmds, &o, &i);
		i++;
	}
}

static char	*trim_input(char *input)
{
	char	*new_input;
	int		aux;
	int		start;
	int		end;
	int		i;

	aux = ft_strlen(input) - 1;
	i = 0;
	while (input[aux] == ' ')
		aux--;
	end = aux;
	aux = 0;
	while (input[aux] && input[aux] == ' ')
		aux++;
	start = aux;
	new_input = (char *)ft_calloc(end - start + 3, 1);
	while (aux <= end)
		new_input[i++] = input[aux++];
	new_input[i] = '\0';
	return (new_input);
}

void	init_commands(t_data *data, t_commands *cmds)
{
	int			i;
	char		*new_input;

	new_input = trim_input(data->user_input);
	cmds->cmds = tokenize_input(new_input, cmds);
	free(new_input);
	i = 0;
	if (cmds->exit_value == 0)
	{
		while (cmds->cmds[i])
			i++;
		cmds->num_cmds = i;
		cmds->paths = get_paths(data->env);
		if (cmds->num_cmds > 0)
			get_operators(data, cmds);
		init_pipes(cmds);
		cmds->pid = (pid_t *)ft_calloc(sizeof(pid_t), cmds->num_cmds + 1);
		cmds->cmd = ft_calloc(cmds->num_cmds, sizeof(t_cmd));
	}
}
