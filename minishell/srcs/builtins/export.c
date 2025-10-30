/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:19:00 by brjoves           #+#    #+#             */
/*   Updated: 2024/02/02 17:12:53 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*add_quotes(char *env)
{
	int		i;
	int		j;
	char	*tmp_char;

	j = 0;
	while (env[j] && env[j++] != '=')
		;
	if (!env[j] && env[j - 1] != '=')
		return (NULL);
	tmp_char = malloc(sizeof(char) * ft_strlen(env) + 3);
	tmp_char[ft_strlen(env) + 2] = '\0';
	i = 0;
	j = 0;
	while (env[j] != '=')
		tmp_char[i++] = env[j++];
	tmp_char[i++] = env[j++];
	tmp_char[i++] = '"';
	while (env[j])
		tmp_char[i++] = env[j++];
	tmp_char[i++] = '"';
	return (tmp_char);
}

static int	print_env(t_data *data)
{
	char	*tmp_char;
	int		i;

	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		tmp_char = add_quotes(data->env[i]);
		if (tmp_char)
			ft_putendl_fd(tmp_char, STDOUT_FILENO);
		else
			ft_putendl_fd(data->env[i], STDOUT_FILENO);
		i++;
		free(tmp_char);
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(t_data *data, t_commands *cmds, int num_cmd)
{
	int		result;
	int		index;

	index = 1;
	result = EXIT_SUCCESS;
	if (!cmds->cmd[num_cmd].args[1])
		return (print_env(data));
	while (cmds->cmd[num_cmd].args[index])
	{
		if (is_valid_var_name(cmds->cmd[num_cmd].args[index]) == false)
		{
			error_msg("export", cmds->cmd[num_cmd].args[index],
				"not a valid identifier", EXIT_FAILURE);
			result = EXIT_FAILURE;
		}
		set_env_var(data, cmds->cmd[num_cmd].args[index], NULL);
		index++;
	}
	return (result);
}
