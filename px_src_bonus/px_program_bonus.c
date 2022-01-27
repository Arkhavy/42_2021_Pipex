/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_program_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:33:33 by ljohnson          #+#    #+#             */
/*   Updated: 2022/01/23 14:13:37 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../px_inc_bonus/pipex_bonus.h"

void	px_bns_outfile(t_ppx px)
{
	char	buffer[1];
	int		index;

	index = 1;
	while (index > 0)
	{
		index = read(px.fd_main, buffer, 1);
		if (index < 0)
			px_bns_exit("PX ERROR : Outfile read failed");
		if (index == 0)
			break ;
		if (write(px.fd_out, buffer, 1) == -1)
			px_bns_exit("PX ERROR : Outfile write error");
	}
	close (px.fd_main);
	close (px.fd_out);
}

int	px_bns_loop(t_ppx px, int a)
{
	pid_t	pid;
	char	**flag;
	int		pipe_fd[2];
	char	*cmd;

	if (pipe(pipe_fd) == -1)
		px_bns_exit("PX ERROR : Loop pipe failed");
	pid = fork();
	if (pid == -1)
		px_bns_exit("PX ERROR : Loop fork failed");
	else if (pid == 0)
	{
		close (pipe_fd[0]);
		px_bns_double_dup(px.fd_main, pipe_fd[1]);
		cmd = px_bns_get_cmd(px, a);
		if (access(cmd, X_OK) == -1)
			px_bns_exit("PX ERROR : Command permission denied");
		flag = ft_split(px.av[a], ' ');
		if (execve(cmd, flag, px.env) == -1)
			px_bns_exit("PX ERROR : Execve failed");
	}
	close (px.fd_main);
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}

int	px_bns_heredoc(t_ppx px)
{
	char	*prompt;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		px_bns_exit("PX ERROR : Here_doc pipe failed");
	prompt = NULL;
	while (1)
	{
		ft_putstr_fd("PX here_doc> ", 1);
		prompt = get_next_line(0);
		if (!px_bns_check_limiter(prompt, px.av[2]))
			break ;
		if (write(pipe_fd[1], prompt, ft_strlen(prompt)) == -1)
			px_bns_exit("PX ERROR : Here_doc write failed");
		free (prompt);
	}
	free (prompt);
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}

int	px_bns_infile(t_ppx px)
{
	int		fd;
	int		pipe_fd[2];
	int		index;
	char	buffer[1];

	fd = open(px.av[1], O_RDONLY);
	if (pipe(pipe_fd) == -1)
		px_bns_exit("PX ERROR : Infile pipe failed");
	index = 1;
	while (index > 0)
	{
		index = read(fd, buffer, 1);
		if (index < 0)
			ft_putendl_fd("PX WARNING : Infile read failed", 2);
		if (index == 0)
			break ;
		if (write(pipe_fd[1], buffer, 1) == -1)
			px_bns_exit("PX ERROR : Infile write failed");
	}
	close (fd);
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}
