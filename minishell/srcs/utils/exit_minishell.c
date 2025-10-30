/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:01:59 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:32:32 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_minishell(t_data *data, int status_code)
{
	free_data(data, true);
	exit(status_code);
}

void	free_exit(t_data *data, t_commands *cmds, int status_code)
{
	close_fds(cmds, true);
	free_cmds(cmds);
	exit_minishell(data, status_code);
}
