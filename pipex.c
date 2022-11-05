/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:12:38 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/05 12:08:12 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_fd_pipe(t_args *args, int argc)
{
	int	i;

	args->fd_pipe = malloc(sizeof(args->fd_pipe) * (argc - 4 - args->here_doc));
	if (!args->fd_pipe)
		return (1);
	i = 0;
	while (i < argc - 4 - args->here_doc)
	{
		args->fd_pipe[i] = malloc(sizeof(args->fd_pipe[i]) * 2);
		if (!args->fd_pipe[i])
		{
			perror("fd_pipe");
			return (free_pipe(args, i), 2);
		}
		i++;
	}
	i = 0;
	while (i < argc - 4 - args->here_doc)
	{
		pipe(args->fd_pipe[i]);
		i++;
	}
	return (0);
}

int	pipex(t_args *args, char **argv, int argc)
{
	int	i;

	if (init_fd_pipe(args, argc) != 0)
		return (1);
	args->pid = malloc(sizeof(args->pid) * (argc - 3 - args->here_doc));
	if (!args->pid)
		return (2);
	i = 0;
	while (i < argc - 3 - args->here_doc)
	{
		args->pid[i] = fork();
		if (args->pid[i] < 0)
			return (perror("fork()"), 3);
		if (args->pid[i] == 0)
			child_proc(args, argv, argc, i);
		i++;
	}
	printf("DEBUG: %d\n", parent_proc(args, argc));
	free(args->pid);
	free_pipe(args, argc - 5 - args->here_doc);
	return (0);
}
