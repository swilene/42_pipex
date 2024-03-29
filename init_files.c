/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:37:04 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/07 15:06:44 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_fds(t_args *args)
{
	args->fd_file1 = open(args->file1, O_RDONLY);
	if (access(args->file1, R_OK) == -1 && args->fd_file1 < 0)
		perror(args->file1);
	args->fd_file2 = open(args->file2, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (args->fd_file2 < 0)
		perror(args->file2);
	return (0);
}

int	init_files(int argc, char **argv, t_args *args)
{
	init_fds(args);
	pipex(args, argv, argc);
	if (args->path)
		free_str(args->path);
	return (0);
}
