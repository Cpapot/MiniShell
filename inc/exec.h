/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:02:33 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/12 19:59:07 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_exec
{
	char	**path;
	int		fd;
	int		in_fd;
	int		out_fd;
	char	**envp;
	pid_t	*pid_tab;
	int		*fd_tab;
	int		end;
}				t_exec;

#endif
