/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:16:04 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:32:59 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_paths(char **envp)
{
	size_t	i;
	char	**paths;
	char	*trim_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
	{
		trim_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
		paths = ft_split(trim_path, ':');
		free(trim_path);
		return (paths);
	}
	else
		return (NULL);
}
