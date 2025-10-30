/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:18:20 by brjoves           #+#    #+#             */
/*   Updated: 2024/02/02 17:12:31 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_work_dir_var(t_data *data, char *path)
{
	set_env_var(data, OLD_PWD, get_env_var_value(data->env, PWD));
	set_env_var(data, PWD, path);
	if (data->old_work_dir)
	{
		free_ptr(data->old_work_dir);
		data->old_work_dir = ft_strdup(data->work_dir);
	}
	if (data->work_dir)
	{
		free_ptr(data->work_dir);
		data->work_dir = ft_strdup(path);
	}
	free(path);
}

static int	change_directory(t_data *data, char *path)
{
	char	*path_pwd;
	char	buf[MAX_PATH];

	if (chdir(path) != 0)
		return (error_msg("cd", path, strerror(errno), 1));
	getcwd(buf, MAX_PATH);
	path_pwd = ft_strdup(buf);
	update_work_dir_var(data, path_pwd);
	return (EXIT_SUCCESS);
}

int	builtin_cd(t_data *data, t_commands *cmds, int i)
{
	char	*path;

	if (!cmds->cmd[i].args[1] || is_space(cmds->cmd[i].args[1][0])
			|| cmds->cmd[i].args[1][0] == '\0'
			|| ft_strncmp(cmds->cmd[i].args[1], "--", 3) == 0
			|| ft_strncmp(cmds->cmd[i].args[1], "~", 2) == 0)
	{
		path = get_env_var_value(data->env, "HOME");
		if (!path || *path == '\0' || is_space(*path))
			return (error_msg("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (change_directory(data, path));
	}
	else if (cmds->cmd[i].args[2])
		return (error_msg("cd", NULL, "too many arguments", EXIT_FAILURE));
	else if (ft_strncmp(cmds->cmd[i].args[1], "-", 2) == 0)
	{
		path = get_env_var_value(data->env, OLD_PWD);
		if (!path)
			return (error_msg("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (change_directory(data, path));
	}
	else
		return (change_directory(data, cmds->cmd[i].args[1]));
}
