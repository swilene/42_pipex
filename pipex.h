/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:10:46 by saguesse          #+#    #+#             */
/*   Updated: 2022/11/07 10:27:03 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "libft/ft_printf/libftprintf.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_args
{
	char	**env;
	char	**path;
	char	*file1;
	char	*file2;
	int		fd_file1;
	int		fd_file2;
	char	**arg;
	char	*prog;
	int		**fd_pipe;
	int		here_doc;
	int		create_hd;
	int		*pid;
	int		exit_code;
}	t_args;

int		init_files(int argc, char **argv, t_args *args);
int		pipex(t_args *args, char **argv, int argc);
char	**get_path(char **envp);
void	free_str(char **str);
void	close_files(t_args *args, int argc, int i);
void	close_fd_pipe(t_args *args, int argc);
int		init_cmds(t_args *args, char *cmd);
void	parent_proc(t_args *args, int argc);
void	child_proc(t_args *args, char **argv, int argc, int i);
void	free_pipe(t_args *args, int i);
int		init_heredoc(t_args *args, char **argv);
char	*check_str(const char *big, const char *little, size_t len);

#endif
