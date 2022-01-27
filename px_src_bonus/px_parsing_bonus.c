/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parsing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:58:48 by ljohnson          #+#    #+#             */
/*   Updated: 2022/01/23 11:56:40 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../px_inc_bonus/pipex_bonus.h"

int	px_bns_check_limiter(char *prompt, char *limiter)
{
	int	a;

	a = 0;
	if (!prompt)
		return (0);
	while (prompt[a] != '\n' && limiter[a])
	{
		if (prompt[a] != limiter[a])
			return (1);
		a++;
	}
	if (prompt[a] == '\n' && limiter[a] == '\0')
		return (0);
	return (1);
}

void	px_bns_double_dup(int fd1, int fd2)
{
	if (dup2(fd1, STDIN_FILENO) == -1)
		px_bns_exit("PX ERROR : STDIN dup failed");
	if (dup2(fd2, STDOUT_FILENO) == -1)
		px_bns_exit("PX ERROR : STDOUT dup failed");
}

static char	*px_bns_get_file(t_ppx px, char *cmd)
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
		px_bns_free_split(px.paths);
		ft_putendl_fd("PX WARNING : Command not found", 2);
		return (cmd);
	}
	return (file);
}

char	*px_bns_get_cmd(t_ppx px, int a)
{
	char	*cmd;
	char	*file;

	if (ft_int_strchr(px.av[a], ' ') > 0)
		cmd = ft_substr(px.av[a], 0, ft_int_strchr(px.av[a], ' '));
	else
		cmd = ft_substr(px.av[a], 0, ft_strlen(px.av[a]));
	if (!access(cmd, F_OK))
		return (cmd);
	file = px_bns_get_file(px, cmd);
	free (cmd);
	return (file);
}

char	**px_bns_get_paths(t_ppx px)
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
