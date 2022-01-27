/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:22:37 by ljohnson          #+#    #+#             */
/*   Updated: 2022/01/22 17:52:14 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/lib_includes/libft.h"
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_ppx
{
	int		ac;
	char	**av;
	char	**env;
	char	**paths;
	int		fd_main;
}	t_ppx;

/*/////////////////////////////////////////////////////////////////////////////
		ALL FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- pipex.c --------------------*/

void	px_free_split(char **split);
void	px_exit(const char *str);
//int	px_check-args(t_ppx px, int ac, char **av);
//void	px_init(t_ppx *px, int ac, char **av, char **env);
//int	main(int ac, char **av, char **env);

/*-------------------- px_parsing.c --------------------*/

void	px_double_dup(int fd1, int fd2);
//char	*px_get_file(t_ppx px, char *cmd);
char	*px_get_cmd(t_ppx px, int a);
char	**px_get_paths(t_ppx px);

/*-------------------- px_program.c --------------------*/

//void	px_child_two(t_ppx px, int pipe_fd);
//int	px_child_one(t_ppx px, int pipe_fd[2]);
void	px_program(t_ppx px);

#endif