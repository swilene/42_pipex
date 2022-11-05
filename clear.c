/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:27:02 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/05 15:19:11 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_pipe(t_args *args, int i)
{
	while (i >= 0)
	{
		if (args->fd_pipe[i])
			free(args->fd_pipe[i]);
		i--;
	}
	free(args->fd_pipe);
}

void	close_fd_pipe(t_args *args, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 4 - args->here_doc)
	{
		if (close(args->fd_pipe[i][0]) < 0)
			ft_printf("fd_pipe[%d][0]: %s\n", i, strerror(errno));
		if (close(args->fd_pipe[i][1]) < 0)
			ft_printf("fd_pipe[%d][1]: %s\n", i, strerror(errno));
		i++;
	}
}

void	close_files(t_args *args, int argc, int i)
{
	if (args->fd_file1 > 0)
	{
		if (close(args->fd_file1) < 0)
			perror(args->file1);
	}
	if (args->here_doc == 1)
	{
		if (i == argc)
		{
			if (unlink(args->file1) < 0)
				perror(args->file1);
		}
		if (args->create_hd == 1)
			free(args->file1);
	}
	if (args->fd_file2 > 0)
	{
		if (close(args->fd_file2) < 0)
			perror(args->file2);
	}
}
