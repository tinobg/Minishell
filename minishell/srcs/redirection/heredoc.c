/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjoves <brjoves@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:23:31 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/26 17:53:31 by brjoves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	exit_heredoc_prompt(char **input, t_redirect *io)
{
	if (*input == NULL)
	{
		ft_putendl_fd("Error: heredoc EOF not found", STDERR_FILENO);
		return (true);
	}
	if (ft_strncmp(*input, io->heredoc_eof, ft_strlen(io->heredoc_eof)) == 0)
		return (true);
	return (false);
}

static bool	heredoc_prompt(t_redirect *io)
{
	int		fd;
	char	*input;

	fd = open(io->in_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	input = NULL;
	while (true)
	{
		signals_wait_cmd();
		input = readline("heredoc> ");
		signals_run_cmd();
		if (exit_heredoc_prompt(&input, io) == true)
			break ;
		ft_putendl_fd(input, fd);
		free_ptr(input);
	}
	close(fd);
	free_ptr(input);
	return (true);
}

static void	get_delimiter(char *part, t_redirect *io)
{
	char	**part_split;
	char	*result;

	part_split = ft_split(part, '<');
	result = ft_strtrim(part_split[0], " ");
	io->heredoc_eof = result;
	free_str(part_split);
}

void	handle_heredoc(t_commands *cmds, char *part)
{
	t_redirect	*io;

	init_redirections(cmds);
	io = cmds->io;
	io->in_file = ".tmp_heredoc";
	get_delimiter(part, io);
	if (heredoc_prompt(io))
		io->fd_in = open(io->in_file, O_RDONLY);
	else
		io->fd_in = -1;
}
