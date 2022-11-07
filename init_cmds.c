/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:47:44 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/07 10:43:25 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_access(char **path, char *cmd)
{
	int		i;
	int		acs;
	char	*right_path;

	acs = access(cmd, F_OK | X_OK);
	if (!path)
		return (ft_printf("%s: %s\n", cmd, strerror(ENOENT)), NULL);
	i = 0;
	acs = -1;
	while (path[i] && acs == -1)
	{
		right_path = ft_strjoin(path[i], cmd);
		if (!right_path)
			return (NULL);
		acs = access(right_path, F_OK | X_OK);
		if (acs < 0)
			free(right_path);
		i++;
	}
	if (acs < 0)
		return (ft_printf("%s: command not found\n", cmd), NULL);
	return (right_path);
}

int	init_cmds(t_args *args, char *cmd)
{
	if (cmd[0] == '.' || cmd[0] == ' ' || cmd[ft_strlen(cmd) - 1] == ' ')
	{
		args->arg = NULL;
		return (ft_printf("%s: %s\n", cmd, strerror(ENOENT)), 1);
	}
	if (cmd[0] == '\0')
	{
		args->arg = NULL;
		return (ft_printf("%s: command not found\n", cmd), 2);
	}
	args->arg = ft_split(cmd, ' ');
	if (!args->arg)
		return (3);
	if (access(cmd, F_OK | X_OK) >= 0)
		args->prog = args->arg[0];
	else
		args->prog = get_access(args->path, args->arg[0]);
	if (!args->prog)
		return (4);
	return (0);
}
