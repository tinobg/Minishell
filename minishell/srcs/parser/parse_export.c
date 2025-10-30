/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:23:56 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 17:19:15 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*check_existing_quotes(char **tmp_p, int num_arg)
{
	int		i;
	int		o;
	char	*tmp_char;

	o = 0;
	while (tmp_p[num_arg][o] && tmp_p[num_arg][o++] != '=')
		;
	if (!tmp_p[num_arg][o] || tmp_p[num_arg][o] == '\"' || \
		tmp_p[num_arg][o] == '\'')
		return (NULL);
	tmp_char = malloc(sizeof(char) * ft_strlen(tmp_p[num_arg]) + 3);
	tmp_char[ft_strlen(tmp_p[num_arg]) + 2] = '\0';
	i = 0;
	o = 0;
	while (tmp_p[num_arg][o] != '=')
		tmp_char[i++] = tmp_p[num_arg][o++];
	tmp_char[i++] = tmp_p[num_arg][o++];
	tmp_char[i++] = '"';
	while (tmp_p[num_arg][o] && tmp_p[num_arg][o] != ' ')
		tmp_char[i++] = tmp_p[num_arg][o++];
	tmp_char[i++] = '"';
	while (tmp_p[num_arg][o])
		tmp_char[i++] = tmp_p[num_arg][o++];
	return (tmp_char);
}

static void	add_quotes(t_commands *cmds, int num_cmd, char **tmp_parser)
{
	char	*tmp_char;
	char	*tmp_char2;
	int		i;
	char	*new_str;

	i = 1;
	new_str = ft_strjoin(tmp_parser[0], " ");
	while (tmp_parser[i])
	{
		tmp_char2 = ft_strjoin(new_str, " ");
		tmp_char = check_existing_quotes(tmp_parser, i);
		free(new_str);
		if (tmp_char != NULL)
			new_str = ft_strjoin(tmp_char2, tmp_char);
		else
			new_str = ft_strjoin(tmp_char2, tmp_parser[i]);
		i++;
		free(tmp_char2);
		free(tmp_char);
	}
	cmds->cmds[num_cmd] = ft_realloc(cmds->cmds[num_cmd], \
			ft_strlen(new_str) + 1);
	ft_strlcpy(cmds->cmds[num_cmd], new_str, ft_strlen(new_str) + 1);
	free(new_str);
}

void	find_export_cmd(t_commands *cmds, int num_cmd)
{
	char	**tmp_parser;
	int		i;

	tmp_parser = parse_whitespace(cmds->cmds[num_cmd]);
	i = 0;
	if (!ft_strncmp("export\0", tmp_parser[0], 7))
		add_quotes(cmds, num_cmd, tmp_parser);
	i = 0;
	while (tmp_parser[i])
		free(tmp_parser[i++]);
	free(tmp_parser[i]);
	free(tmp_parser);
}
