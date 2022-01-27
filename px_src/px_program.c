/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:06:11 by ljohnson          #+#    #+#             */
/*   Updated: 2022/01/22 17:59:27 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../px_inc/pipex.h"

static void	px_child_two(t_ppx px, int pipe_fd)
{
	int		fd;
	char	**flag;
	char	*cmd;

	fd = open(px.av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_putendl_fd("PX WARNING : Outfile open failed", 2);
	flag = ft_split(px.av[3], ' ');
	px_double_dup(pipe_fd, fd);
	cmd = px_get_cmd(px, 3);
	if (access(cmd, X_OK) == -1)
		px_exit("PX ERROR : Cannot access second command ");
	if (execve(cmd, flag, px.env) == -1)
		px_exit("PX ERROR : Second execve failed ");
	close (pipe_fd);
	close (fd);
	free (cmd);
	px_free_split(flag);
	exit(0);
}

static int	px_child_one(t_ppx px, int pipe_fd[2])
{
	int		fd;
	char	**flag;
	char	*cmd;

	fd = open(px.av[1], O_RDONLY);
	if (fd == -1)
		px_exit("PX ERROR : Infile open failed ");
	flag = ft_split(px.av[2], ' ');
	px_double_dup(fd, pipe_fd[1]);
	close (pipe_fd[0]);
	cmd = px_get_cmd(px, 2);
	if (access(cmd, X_OK) == -1)
		px_exit("PX ERROR : Cannot access first command ");
	if (execve(cmd, flag, px.env) == -1)
		px_exit("PX ERROR : First execve failed ");
	close(fd);
	free (cmd);
	px_free_split(flag);
	return (pipe_fd[1]);
}

void	px_program(t_ppx px)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
		px_exit("PX ERROR : Pipe failed ");
	pid1 = fork();
	if (pid1 == -1)
		px_exit("PX ERROR : Fork failed ");
	if (pid1 == 0)
		pipe_fd[0] = px_child_one(px, pipe_fd);
	pid2 = fork();
	if (pid2 == -1)
		px_exit("PX ERROR : Fork failed ");
	close (pipe_fd[1]);
	if (pid2 == 0)
		px_child_two(px, pipe_fd[0]);
	if (waitpid(pid1, 0, 0) == -1)
		px_exit("PX ERROR : Waitpid failed ");
	if (waitpid(pid2, 0, 0) == -1)
		px_exit("PX ERROR : Waitpid failed ");
}
