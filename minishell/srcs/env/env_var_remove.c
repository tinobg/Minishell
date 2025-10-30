/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:09:03 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/31 10:04:45 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env_var_remove(t_data *data, int index)
{
	int	i;
	int	j;

	free_ptr(data->env[index]);
	i = index;
	j = index;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		i++;
		j++;
	}
	data->env = env_var_realloc(data, j);
}

char	**env_var_realloc(t_data *data, int len)
{
	char	**new_env_var;
	int		i;

	i = 0;
	new_env_var = ft_calloc((len + 1), sizeof * new_env_var);
	if (!new_env_var)
		return (NULL);
	while (data->env[i] && i < len)
	{
		new_env_var[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free_ptr(data->env);
	return (new_env_var);
}
