/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:57:50 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/04 18:37:53 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*check_equal(char *var)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!ft_strchr(var, '='))
		tmp = ft_strjoin(var, "=");
	else
	{
		while (var[i++] != '=')
			;
		tmp = (char *)malloc(sizeof(char) * i + 2);
		tmp[i] = '\0';
		ft_strlcpy(tmp, var, i + 1);
	}
	return (tmp);
}

int	get_env_var_index(char **env, char *var)
{
	int		i;
	char	*tmp;
	char	*tmp_env;

	i = 0;
	tmp = check_equal(var);
	if (!tmp)
		return (-1);
	while (env[i])
	{
		tmp_env = check_equal(env[i]);
		if (ft_strncmp(tmp, tmp_env, ft_strlen(tmp_env)) == 0)
		{
			free(tmp_env);
			free_ptr(tmp);
			return (i);
		}
		i++;
		free(tmp_env);
	}
	free_ptr(tmp);
	return (-1);
}

int	env_var_count(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

char	*get_env_var_value(char **envp, char *var)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(tmp, envp[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			result = ft_strchr(envp[i], '=') + 1;
			return (result);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}
