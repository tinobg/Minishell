/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:28:38 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:11:17 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	exec_cmd(t_data *data)
{
	t_commands	*cmds;
	int			status_code;

	cmds = (t_commands *)ft_calloc(1, sizeof(t_commands));
	cmds->exit_value = 0;
	status_code = 0;
	init_commands(data, cmds);
	if (cmds->exit_value == 0)
	{
		init_cmd(data, cmds, 0);
		cmds->exit_value = execute(data, cmds);
	}
	if (status_code == 0 && cmds->exit_value != 0)
		status_code = cmds->exit_value;
	close_fds(cmds, false);
	free_cmds(cmds);
	return (status_code);
}

static void	init_prompt(t_data *data)
{
	char	*prompt;

	while (true)
	{
		signals_wait_cmd();
		prompt = get_prompt();
		data->user_input = readline(prompt);
		signals_run_cmd();
		free_ptr(prompt);
		if (input_handler(data))
			g_status_code = exec_cmd(data);
		else
			g_status_code = 0;
		free_data(data, false);
	}
	exit_minishell(data, g_status_code);
}

int	minishell(int argc, char **argv, char **envp)
{
	t_data	data;

	if (check_args(argc, argv) == false || init_data(&data, envp) == false)
		exit_minishell(NULL, EXIT_FAILURE);
	init_prompt(&data);
	return (0);
}
