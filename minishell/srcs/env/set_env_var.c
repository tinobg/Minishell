/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:02:03 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/31 10:04:54 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	set_env_var(t_data *data, char *key, char *value)
{
	char	*tmp;
	int		i;

	i = get_env_var_index(data->env, key);
	if (value != NULL && !ft_strchr(key, '='))
		tmp = ft_strjoin("=", value);
	else
		tmp = ft_strdup("\0");
	if (i != -1 && data->env[i])
	{
		free_ptr(data->env[i]);
		data->env[i] = ft_strjoin(key, tmp);
	}
	else
	{
		i = env_var_count(data->env);
		data->env = env_var_realloc(data, (i + 1));
		if (data->env)
			return (false);
		data->env[i] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}
