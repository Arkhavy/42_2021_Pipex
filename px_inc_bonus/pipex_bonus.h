/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:48:56 by ljohnson          #+#    #+#             */
/*   Updated: 2022/01/23 10:37:35 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/lib_includes/libft.h"
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_ppx
{
	int		ac;
	char	**av;
	char	**env;
	char	**paths;
	int		hrdc;
	int		fd_main;
	int		fd_out;
}	t_ppx;

/*/////////////////////////////////////////////////////////////////////////////
		ALL FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- pipex_bonus.c --------------------*/

void	px_bns_free_split(char **split);
void	px_bns_exit(const char *str);
//int	px_bns_check_args(t_ppx px, int ac, char **av);
//void	px_bns_init(t_ppx *px, int ac, char **av, char **env);
//int	main(int ac, char **av, char **env);

/*-------------------- px_parsing_bonus.c --------------------*/

int		px_bns_check_limiter(char *prompt, char *limiter);
//char	*px_bns_get_file(t_ppx px, char *cmd);
void	px_bns_double_dup(int fd1, int fd2);
char	*px_bns_get_cmd(t_ppx px, int a);
char	**px_bns_get_paths(t_ppx px);

/*-------------------- px_program_bonus.c --------------------*/

void	px_bns_outfile(t_ppx px);
int		px_bns_loop(t_ppx px, int a);
int		px_bns_heredoc(t_ppx px);
int		px_bns_infile(t_ppx px);

#endif