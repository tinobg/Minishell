/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjoves <brjoves@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:05 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/04 16:11:35 by brjoves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_outfile(t_commands *cmds, char *file, bool trunc)
{
	cmds->io->out_file = file;
	if (cmds->io->out_file && cmds->io->out_file[0] == '\0')
		return (error_msg(file, NULL, "ambiguous redirect", false));
	if (trunc == true)
		cmds->io->fd_out = open(cmds->io->out_file, O_WRONLY | O_CREAT
				| O_TRUNC, 0664);
	else
		cmds->io->fd_out = open(cmds->io->out_file, O_WRONLY | O_CREAT
				| O_APPEND, 0664);
	if (cmds->io->fd_out == -1)
		return (error_msg(cmds->io->out_file, NULL, strerror(errno),
				false));
	return (-1);
}

int	handle_output(t_commands *cmds, char *part, bool trunc)
{
	char	**part_split;
	char	*result;
	int		status_code;

	part_split = ft_split(part, '>');
	result = ft_strtrim(part_split[0], " ");
	init_redirections(cmds);
	status_code = open_outfile(cmds, result, trunc);
	free_str(part_split);
	if (status_code != -1)
		cmds->io->error = true;
	else
		cmds->io->error = false;
	return (status_code);
}
