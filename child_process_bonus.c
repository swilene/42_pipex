/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:04:59 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/07 15:02:11 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_before_dup(t_args *args, int argc, int i, int j)
{
	while (j < argc - 4 - args->here_doc)
	{
		if (i - 1 != j)
		{
			if (close(args->fd_pipe[j][0]) < 0)
				ft_printf("fd_pipe[%d][1]: %s\n", j, strerror(errno));
		}
		if (i != j)
		{
			if (close(args->fd_pipe[j][1]) < 0)
				ft_printf("fd_pipe[%d][1]: %s\n", j, strerror(errno));
		}
		j++;
	}
	if (i != 0 && args->fd_file1 > 0)
	{
		if (close(args->fd_file1) < 0)
			perror(args->file1);
	}
	if (i != argc - 4 - args->here_doc && args->fd_file2 > 0)
	{
		if (close(args->fd_file2) < 0)
			perror(args->file2);
	}
}

void	close_after_dup(t_args *args, int argc, int i)
{
	if (i == 0 && args->fd_file1 > 0)
	{
		if (close(args->fd_file1) < 0)
			perror(args->file1);
	}
	else
	{
		if (close(args->fd_pipe[i - 1][0]) < 0)
			ft_printf("fd_pipe[%d][1]: %s\n", i - 1, strerror(errno));
	}
	if (i == argc - 4 - args->here_doc && args->fd_file2 > 0)
	{
		if (close(args->fd_file2) < 0)
			perror(args->file2);
	}
	else
	{
		if (close(args->fd_pipe[i][1]) < 0)
			ft_printf("fd_pipe[%d][1]: %s\n", i, strerror(errno));
	}
}

void	free_before_exit(t_args *args, int argc, int i)
{
	close_fd_pipe(args, argc);
	close_files(args, argc, i);
	if (args->path)
		free_str(args->path);
	if (args->arg)
		free_str(args->arg);
	free_pipe(args, argc - 5 - args->here_doc);
	free(args->pid);
}

int	check_before_dup(t_args *args, char **argv, int argc, int i)
{
	if ((i == 0 && args->fd_file1 < 0) || (i == argc - 4 - args->here_doc
			&& args->fd_file2 < 0))
	{
		args->arg = NULL;
		free_before_exit(args, argc, i);
		args->exit_code = 1;
		return (1);
	}
	if (init_cmds(args, argv[i + 2 + args->here_doc]))
	{
		free_before_exit(args, argc, i);
		args->exit_code = 127;
		return (2);
	}
	return (0);
}

void	child_proc(t_args *args, char **argv, int argc, int i)
{
	int	err_dup_r;
	int	err_dup_w;

	if (check_before_dup(args, argv, argc, i))
		exit(args->exit_code);
	close_before_dup(args, argc, i, 0);
	if (i == 0 && args->fd_file1 > 0)
		err_dup_r = dup2(args->fd_file1, STDIN_FILENO);
	else
		err_dup_r = dup2(args->fd_pipe[i - 1][0], STDIN_FILENO);
	if (i == argc - 4 - args->here_doc && args->fd_file2 > 0)
		err_dup_w = dup2(args->fd_file2, STDOUT_FILENO);
	else
		err_dup_w = dup2(args->fd_pipe[i][1], STDOUT_FILENO);
	close_after_dup(args, argc, i);
	if (err_dup_r < 0 || err_dup_w < 0)
	{
		perror("dup2");
		free_before_exit(args, argc, i);
		exit(2);
	}
	exit(execve(args->prog, args->arg, args->env));
}
