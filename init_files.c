/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:37:04 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/05 15:28:59 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_str(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	if (little[j] == '\0')
		return ((char *)big);
	while (big[i] && little[j] && len > 0)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0' && big[j + i + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

int	init_fds(t_args *args)
{
	args->here_doc = 0;
	args->fd_file1 = open(args->file1, O_RDONLY);
	if (access(args->file1, R_OK) == 0 && args->fd_file1 < 0)
		perror(args->file1);
	args->fd_file2 = open(args->file2, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (args->fd_file2 < 0)
		perror(args->file2);
	return (0);
}

int	init_files(int argc, char **argv, t_args *args)
{
	if (!check_str(args->file1, "here_doc", 8))
		init_fds(args);
	else
		init_heredoc(args, argv);
	pipex(args, argv, argc);
	if (args->path)
		free_str(args->path);
	return (0);
}
