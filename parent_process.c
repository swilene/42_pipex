/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:18:39 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/07 10:27:57 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_proc(t_args *args, int argc)
{
	int	wstatus;
	int	i;

	close_fd_pipe(args, argc);
	close_files(args, argc, argc);
	i = 0;
	while (i < argc - 3 - args->here_doc)
	{
		waitpid(args->pid[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			args->exit_code = WEXITSTATUS(wstatus);
		i++;
	}
}
