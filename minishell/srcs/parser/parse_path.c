/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjoves <brjoves@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:19:47 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/04 16:11:47 by brjoves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cmd_path(t_commands *cmds, int index)
{
	int		i;
	char	*cmd_comp;
	char	*cmd;

	cmd = ft_strdup("/");
	cmd = ft_strsjoin(cmd, cmds->cmd[index].args[0]);
	i = 0;
	if (cmds->paths)
	{
		while (cmds->paths[i])
		{
			cmd_comp = ft_strjoin(cmds->paths[i], cmd);
			if (access(cmd_comp, F_OK | X_OK) == 0)
			{
				free_ptr(cmd);
				return (cmd_comp);
			}
			free_ptr(cmd_comp);
			i++;
		}
	}
	free_ptr(cmd);
	return (NULL);
}
