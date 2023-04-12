/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:05:38 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/12 18:53:23 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include					"../inc/minishell.h"
#define		PWDERROR		"Error while calling \"getcwd\""
#define		BUFFER_SIZE		2048

static char	*get_logpath(t_info *info)
{
	static char	*logpath = NULL;
	char		*result;
	char		buffer[BUFFER_SIZE];

	if (logpath != NULL)
	{
		result = ft_strdup(logpath, &info->parsing);
		return (result);
	}
	if (getcwd(buffer, BUFFER_SIZE) == NULL)
	{
		ft_error(PWDERROR, info);
		return (NULL);
	}
	logpath = ft_strjoin(buffer, "/.log", &info->shell_mem);
	if (logpath == NULL)
		ft_error(ERROR99, info);
	result = ft_strdup(logpath, &info->parsing);
	return (result);
}

static char	*get_pwd(t_info *info)
{
	char		*pwd;
	char		buffer[BUFFER_SIZE];

	if (getcwd(buffer, BUFFER_SIZE) == NULL)
	{
		ft_error(PWDERROR, info);
		return (NULL);
	}
	pwd = ft_strdup(buffer, &info->exec_mem);
	if (pwd == NULL)
		ft_error(ERROR99, info);
	return (pwd);
}

void	addto_logs(char *commands, t_info *info)
{
	int		log_fd;
	char	*path;
	char	*login;
	char	*logpath;

	path = get_pwd(info);
	if (!path)
		print_error_exit(info, "Failure to acces or create logs", 0);
	logpath = get_logpath(info);
	if (!logpath)
		print_error_exit(info, "Failure to acces or create logs", 0);
	log_fd = open(logpath, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (log_fd == -1)
		print_error_exit(info, "Failure to acces or create logs", 0);
	login = getenv("LOGNAME");
	ft_printf_fd(log_fd, "LOGNAME: \"%s\"	PATH: \"%s\"\n", login, path);
	ft_printf_fd(log_fd, "	COMMAND: \"%s\"\n", commands);
}
