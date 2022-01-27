/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:25:27 by ljohnson          #+#    #+#             */
/*   Updated: 2022/01/23 11:40:56 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../px_inc/pipex.h"

void	px_free_split(char **split)
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

void	px_exit(const char *str)
{
	if (str)
	{
		perror(str);
		exit(1);
	}
	else
		exit(0);
}

static int	px_check_args(int ac, char **av)
{
	int	a;

	a = 0;
	if (ac != 5)
		return (0);
	while (a < ac)
	{
		if (ft_ischarset(av[a][0], "\t\r\n\v\f"))
			return (0);
		a++;
	}
	if (access(av[1], F_OK) == -1)
		ft_putendl_fd("PX WARNING : Infile does not exist", 2);
	else if (access(av[1], R_OK) == -1)
		ft_putendl_fd("PX WARNING : Infile permission denied", 2);
	return (1);
}

static void	px_init(t_ppx *px, int ac, char **av, char **env)
{
	px->ac = ac;
	px->av = av;
	px->env = env;
	if (!px_check_args(ac, av))
		px_exit("PX ERROR : Args not valid");
	px->paths = px_get_paths(*px);
}

int	main(int ac, char **av, char **env)
{
	t_ppx	px;

	px_init(&px, ac, av, env);
	px_program(px);
	px_free_split(px.paths);
	return (0);
}
