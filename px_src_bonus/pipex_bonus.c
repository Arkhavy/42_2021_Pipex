/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:51:39 by ljohnson          #+#    #+#             */
/*   Updated: 2022/01/23 14:40:29 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../px_inc_bonus/pipex_bonus.h"

void	px_bns_free_split(char **split)
{
	int	a;

	a = 0;
	while (split[a])
	{
		free (split[a]);
		a++;
	}
	free (split);
}

void	px_bns_exit(const char *str)
{
	if (str)
	{
		perror(str);
		exit(1);
	}
	else
		exit (0);
}

static int	px_bns_check_args(t_ppx px, int ac, char **av)
{
	int	a;

	a = 2 + px.hrdc;
	if (ac < 5 + px.hrdc)
		return (0);
	while (a < ac)
	{
		if (ft_ischarset(av[a][0], "\t\r\n\v\f"))
			return (0);
		a++;
	}
	return (1);
}

static void	px_bns_init(t_ppx *px, int ac, char **av, char **env)
{
	px->ac = ac;
	px->av = av;
	px->env = env;
	px->paths = px_bns_get_paths(*px);
	if (!av[1] || !av[1][0])
		px_bns_exit("PX ERROR : First arg not valid");
	px->hrdc = 1;
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc") + 1))
		px->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		px->hrdc = 0;
		if (access(av[1], F_OK) == -1)
			ft_putendl_fd("PX WARNING : Infile does not exist", 2);
		else if (access(av[1], R_OK) == -1)
			ft_putendl_fd("PX WARNING : Infile permission denied", 2);
		px->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (px->fd_out < 0)
		ft_putendl_fd("PX WARNING : Outfile open failed", 2);
	if (access(av[ac - 1], W_OK) == -1)
		ft_putendl_fd("PX WARNING : Outfile permission denied", 2);
	if (!px_bns_check_args(*px, ac, av))
		px_bns_exit("PX ERROR : Args not valid");
}

int	main(int ac, char **av, char **env)
{
	t_ppx	px;
	int		a;

	px_bns_init(&px, ac, av, env);
	if (px.hrdc == 1)
		px.fd_main = px_bns_heredoc(px);
	else
		px.fd_main = px_bns_infile(px);
	a = 2 + px.hrdc;
	while (a < ac - 1)
	{
		px.fd_main = px_bns_loop(px, a);
		a++;
	}
	while (a > 2 + px.hrdc)
	{
		if (waitpid(-1, 0, 0) == -1)
			px_bns_exit("PX ERROR : Waitpid failed");
		a--;
	}
	px_bns_outfile(px);
	px_bns_free_split(px.paths);
	exit(0);
	return (0);
}
