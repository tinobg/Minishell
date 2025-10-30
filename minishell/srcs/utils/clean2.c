/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjoves <brjoves@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:22:01 by brjoves           #+#    #+#             */
/*   Updated: 2024/02/02 16:23:22 by brjoves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i])
			{
				free_ptr(str[i]);
				str[i] = NULL;
			}
			i++;
		}
		free(str);
		str = NULL;
	}
}

bool	clear_prev_input(t_redirect *io, bool in_file)
{
	if (in_file == true && io->in_file)
	{
		if (io->fd_in == -1 || (io->out_file && io->fd_out == -1))
			return (false);
		if (io->heredoc_eof != NULL)
		{
			free_ptr(io->heredoc_eof);
			io->heredoc_eof = NULL;
			unlink(io->in_file);
		}
		free_ptr(io->in_file);
		close(io->fd_in);
	}
	else if (in_file == false && io->out_file)
	{
		if (io->fd_out == -1 || (io->in_file && io->fd_in == -1))
			return (false);
		free_ptr(io->out_file);
		close(io->fd_out);
	}
	return (true);
}

void	free_data(t_data *data, bool exit_shell)
{
	if (data)
	{
		if (data->user_input)
			free_ptr(data->user_input);
		if (exit_shell)
		{
			if (data->old_work_dir)
				free_ptr(data->old_work_dir);
			if (data->work_dir)
				free_ptr(data->work_dir);
			if (data->env)
				free_str(data->env);
			rl_clear_history();
		}
	}
}

void	free_pipes(t_commands *cmds)
{
	int	i;

	i = 0;
	if (cmds->pipe)
	{
		while (i < cmds->num_exec)
		{
			if (cmds->pipe[i].fd)
				free(cmds->pipe[i].fd);
			i++;
		}
		free(cmds->pipe);
	}
}
