/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:49:05 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:42:57 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	change_cmd(t_commands *cmds, int num_cmd)
{
	char	*tmp_char;

	tmp_char = rm_redirections(cmds->cmds[num_cmd]);
	free(cmds->cmds[num_cmd]);
	cmds->cmds[num_cmd] = (char *)malloc(ft_strlen(tmp_char) * \
						sizeof(char) + 1);
	cmds->cmds[num_cmd][ft_strlen(tmp_char)] = '\0';
	ft_strlcpy(cmds->cmds[num_cmd], tmp_char, ft_strlen(tmp_char) + 1);
	free(tmp_char);
}

void	init_cmd(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	i = num_cmd;
	while (i < cmds->num_cmds)
	{
		cmds->cmd[i].redirections = parse_redirections(cmds->cmds[i]);
		change_cmd(cmds, i);
		if (cmds->cmds[i][0] && cmds->cmds[i][0] != ' ')
			parse_dollar_sign(data, cmds, i);
		cmds->cmd[i].args = parser(cmds->cmds[i]);
		if (cmds->operators[i] && cmds->operators[i] == PIPE)
			i++;
		else
			i = cmds->num_cmds;
	}
}

void	init_single_cmd(t_data *data, t_commands *cmds, int num_cmd)
{
	int	i;

	i = 0;
	i = num_cmd;
	if (i < cmds->num_cmds)
	{
		cmds->cmd[i].redirections = parse_redirections(cmds->cmds[i]);
		change_cmd(cmds, i);
		if (cmds->cmds[i][0] && cmds->cmds[i][0] != ' ')
			parse_dollar_sign(data, cmds, i);
		cmds->cmd[i].args = parser(cmds->cmds[i]);
	}
}
