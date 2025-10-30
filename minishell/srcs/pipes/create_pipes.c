/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjoves <brjoves@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:01:31 by brjoves           #+#    #+#             */
/*   Updated: 2024/02/02 16:01:33 by brjoves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_pipes(t_commands *cmds, int index)
{
	if (index == 0)
		check_pipes(cmds, index);
	else
	{
		if (cmds->operators[index])
			check_pipes(cmds, index);
		if (cmds->operators[index - 1] == PIPE)
			dup2(cmds->pipe[index].fd[0], STDIN);
	}
	close_pipes(cmds);
}
