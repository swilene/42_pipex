/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:59:09 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/07 15:03:57 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*create_heredoc(t_args *args, int acs)
{
	int		i;
	char	*file;
	char	*nb;

	i = 0;
	while (acs == 0 && i <= INT_MAX)
	{
		nb = ft_itoa(i);
		if (nb)
		{
			file = ft_strjoin(args->file1, nb);
			free(nb);
			if (file)
			{
				acs = access(file, F_OK);
				if (acs == 0)
					free(file);
			}
		}
		i++;
	}
	return (file);
}

int	open_heredoc(t_args *args)
{
	int		acs;

	acs = access(args->file1, F_OK);
	if (acs < 0)
	{
		args->fd_file1 = open(args->file1, O_RDWR | O_CREAT, 00644);
		args->create_hd = 0;
		if (args->fd_file1 < 0)
			return (perror(args->file1), 1);
		return (0);
	}
	else
	{
		args->file1 = create_heredoc(args, acs);
		args->fd_file1 = open(args->file1, O_WRONLY | O_CREAT, 00644);
		args->create_hd = 1;
		if (args->fd_file1 < 0)
			return (perror(args->file1), 2);
	}
	return (0);
}

void	wait_limiter(t_args *args, char *limiter)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (check_str(line, limiter, ft_strlen(limiter)) != NULL)
		{
			if (close(args->fd_file1) < 0)
				perror(args->file1);
			free(line);
			break ;
		}
		write(args->fd_file1, line, ft_strlen(line));
		free(line);
	}
}

int	init_heredoc(t_args *args, char **argv)
{
	char	*limiter;

	args->here_doc = 1;
	if (open_heredoc(args))
		return (1);
	limiter = ft_strjoin(argv[2], "\n");
	if (!limiter)
		return (2);
	wait_limiter(args, limiter);
	free(limiter);
	args->fd_file1 = open(args->file1, O_RDONLY);
	if (args->fd_file1 < 0)
		return (perror(args->file1), 3);
	args->fd_file2 = open(args->file2, O_RDWR | O_CREAT | O_APPEND, 00644);
	if (args->fd_file2 < 0)
		return (perror(args->file2), 4);
	return (0);
}
