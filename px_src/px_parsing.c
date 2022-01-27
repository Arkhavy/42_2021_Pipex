/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:38:56 by ljohnson          #+#    #+#             */
/*   Updated: 2022/01/23 10:20:57 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../px_inc/pipex.h"

void	px_double_dup(int fd1, int fd2)
{
	if (dup2(fd1, STDIN_FILENO) == -1)
		px_exit("PX ERROR : STDIN Dup failed ");
	if (dup2(fd2, STDOUT_FILENO) == -1)
		px_exit("PX ERROR : STDOUT Dup failed ");
}

static char	*px_get_file(t_ppx px, char *cmd)
{
	int		b;
	char	*tmp;
	char	*file;

	b = 0;
	file = NULL;
	while (px.paths[b])
	{
		tmp = file;
		file = ft_strjoin(px.paths[b], cmd);
		free (tmp);
		if (!access (file, F_OK))
			break ;
		b++;
	}
	if (access(file, F_OK) == -1)
	{
		free (file);
		px_free_split(px.paths);
		ft_putendl_fd("PX WARNING : Command not found", 2);
		return (cmd);
	}
	return (file);
}

char	*px_get_cmd(t_ppx px, int a)
{
	char	*cmd;
	char	*file;

	if (ft_int_strchr(px.av[a], ' ') > 0)
		cmd = ft_substr(px.av[a], 0, ft_int_strchr(px.av[a], ' '));
	else
		cmd = ft_substr(px.av[a], 0, ft_strlen(px.av[a]));
	if (!access(cmd, F_OK))
		return (cmd);
	file = px_get_file(px, cmd);
	free (cmd);
	return (file);
}

char	**px_get_paths(t_ppx px)
{
	char	**paths;
	char	*tmp;
	int		a;

	a = 0;
	while (ft_strncmp(px.env[a], "PATH=", 5))
		a++;
	paths = ft_split(&px.env[a][5], ':');
	if (!paths)
		return (NULL);
	a = 0;
	while (paths[a])
	{
		tmp = paths[a];
		paths[a] = ft_strjoin(paths[a], "/");
		free (tmp);
		a++;
	}
	return (paths);
}
