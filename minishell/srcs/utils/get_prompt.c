/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:20:54 by jubaldo           #+#    #+#             */
/*   Updated: 2024/01/14 15:21:26 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_prompt(void)
{
	char	*cwd;
	char	*prompt;
	int		len;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("minishell$ "));
	len = ft_strlen(cwd) + ft_strlen("minishell: ") + 3;
	prompt = malloc(len);
	if (!prompt)
	{
		free(cwd);
		return (NULL);
	}
	ft_strcpy(prompt, "minishell: ");
	ft_strcat(prompt, cwd);
	ft_strcat(prompt, "$ ");
	free(cwd);
	return (prompt);
}
