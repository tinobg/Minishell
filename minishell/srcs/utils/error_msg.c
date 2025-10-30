/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:23:57 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/31 17:06:33 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	with_quotes(char *cmd)
{
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (true);
	return (false);
}

int	error_msg(char *cmd, char *spec, char *msg, int status_code)
{
	char	*error_msg;
	bool	is_quote;

	if (cmd != NULL)
		is_quote = with_quotes(cmd);
	error_msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		error_msg = ft_strsjoin(error_msg, cmd);
		error_msg = ft_strsjoin(error_msg, ": ");
	}
	if (spec != NULL)
	{
		if (is_quote)
			error_msg = ft_strsjoin(error_msg, "`");
		error_msg = ft_strsjoin(error_msg, spec);
		if (is_quote)
			error_msg = ft_strsjoin(error_msg, "'");
		error_msg = ft_strsjoin(error_msg, ": ");
	}
	error_msg = ft_strsjoin(error_msg, msg);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	free_ptr(error_msg);
	return (status_code);
}
