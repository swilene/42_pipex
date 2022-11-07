/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:09:57 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/07 10:58:35 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_args	args;
	
	if (argc >= 5)
	{
		args.env = envp;
		args.file1 = argv[1];
		args.file2 = argv[argc - 1];
		args.path = get_path(envp);
		init_files(argc, argv, &args);
	}
	else
		args.exit_code = 127;
	return (args.exit_code);
}
