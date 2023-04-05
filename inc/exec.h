/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:02:33 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/05 04:25:53 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_exec
{
	char	**path;
	int		fd;
	char	**envp;
	pid_t	*pid_tab;
	int		*fd_tab;
	// int		in_fd;
	// int		out_fd;
}				t_exec;

#endif
