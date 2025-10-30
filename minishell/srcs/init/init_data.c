/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:37:49 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/25 14:44:22 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	init_env(t_data *data, char **envp)
{
	int	i;

	data->env = ft_calloc(env_var_count(envp) + 1, sizeof * data->env);
	if (!data->env)
		return (false);
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (true);
}

bool	init_path(t_data *data)
{
	char	path[MAX_PATH];
	char	*cwd;

	cwd = getcwd(path, MAX_PATH);
	data->work_dir = ft_strdup(cwd);
	if (!data->work_dir)
		return (false);
	if (get_env_var_index(data->env, OLD_PWD) != -1)
		data->old_work_dir = ft_strdup(get_env_var_value(data->env, OLD_PWD));
	else
		data->old_work_dir = ft_strdup(cwd);
	return (true);
}

bool	init_data(t_data *data, char **envp)
{
	if (!init_env(data, envp))
		return (false);
	if (!init_path(data))
		return (false);
	data->user_input = NULL;
	return (true);
}
