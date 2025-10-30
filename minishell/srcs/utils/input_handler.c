/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:43:54 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/25 17:49:54 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_emptystring(char *str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (true);
	while (*str != '\0')
	{
		if (!is_space((unsigned char)*str))
			return (false);
		str++;
	}
	return (true);
}

bool	input_handler(t_data *data)
{
	if (!data->user_input)
	{
		ft_putendl_fd("exit", STDOUT);
		exit_minishell(data, 0);
	}
	else if (data->user_input == NULL
		|| ft_strncmp(data->user_input, "\0", 1) == 0)
		return (false);
	else if (is_emptystring(data->user_input) == true)
		return (false);
	add_history(data->user_input);
	return (true);
}
