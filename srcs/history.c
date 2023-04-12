/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:05:38 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/12 16:09:34 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	addto_logs(char *commands, t_info *info)
{
	int		log_fd;
	char	*path;
	char	*login;
	const char *logpath = NULL;

	path = getenv("PWD");
	if (logpath == NULL)
	{
		logpath = ft_strjoin(path, ".log", &info->shell_mem);
	}
	log_fd = open(logpath, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (log_fd == -1)
		print_error_exit(info, "Failure to acces or create logs", 0);
	login = getenv("LOGNAME");
	ft_printf_fd(log_fd, "LOGNAME: \"%s\"	PATH: \"%s\"\n", login, path);
	ft_printf_fd(log_fd, "	COMMAND: \"%s\"\n", commands);
}
