/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:20:22 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/19 17:44:29 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define GITBUFFER_SIZE	1024
#define GITPATH			"/.git/HEAD"

static char	*get_gitbranch_indir(char *buffer, char *dir, t_info *info)
{
	char	*result;
	int		fd;
	ssize_t	rd;
	char	*path;

	path = ft_strjoin(dir, GITPATH, &info->prompt_mem);
	if (path == NULL)
		ft_error(ERROR99, info);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	rd = read(fd, buffer, GITBUFFER_SIZE);
	close (fd);
	if (rd == -1)
		return (NULL);
	buffer[rd - 1] = '\0';
	if (ft_strncmp(buffer, "ref: refs/heads/", 16) != 0)
		return (NULL);
	result = ft_stsubstr(buffer, 16, rd - 16, &info->prompt_mem);
	if (result == NULL)
		ft_error(ERROR99, info);
	return (result);
}

static int	dir_len(char *dir)
{
	int	len;

	len = ft_strlen(dir);
	while (len != 0)
	{
		len--;
		if (dir[len] == '/')
			return (len);
	}
	return (-1);
}

static char	*get_gitbranch_in_parentdir(t_info *info)
{
	char	*dir;
	char	buffer[GITBUFFER_SIZE];
	char	*result;
	int		dir_size;

	dir = ft_strdup(getcwd(buffer, GITBUFFER_SIZE), &info->prompt_mem);
	while (dir != NULL)
	{
		ft_bzero(buffer, GITBUFFER_SIZE);
		result = get_gitbranch_indir(buffer, dir, info);
		if (result != NULL)
			return (result);
		dir_size = dir_len(dir);
		if (dir_size == -1)
			break ;
		dir = ft_stsubstr(dir, 0, dir_size, &info->prompt_mem);
		if (dir == NULL)
			ft_error(ERROR99, info);
	}
	return (NULL);
}

static char	*get_prompt_path(t_info *info)
{
	char	*dir;
	char	buffer[GITBUFFER_SIZE];
	char	*result;

	dir = getcwd(buffer, GITBUFFER_SIZE);
	result = ft_stsubstr(dir, dir_len(dir) + 1, \
		ft_strlen(dir), &info->prompt_mem);
	if (result == NULL)
		ft_error(ERROR99, info);
	return (result);
}

/*
	Return a string who contain the actual directory and the name of the branch
*/
char	*prompt_string(t_info *info)
{
	char	*prompt;
	char	*branch;
	char	*path;

	branch = get_gitbranch_in_parentdir(info);
	path = get_prompt_path(info);
	prompt = ft_strjoin("\n\001\e[36m\002\001➡️\002  ", path, &info->prompt_mem);
	prompt = ft_strjoin(prompt, " "WHITE, &info->prompt_mem);
	if (prompt == NULL)
		ft_error(ERROR99, info);
	if (branch != NULL)
	{
		prompt = ft_strjoin(prompt, "\001\e[34m\002git:(\001\x1b[31m\002", \
			&info->prompt_mem);
		if (prompt == NULL)
			ft_error(ERROR99, info);
		prompt = ft_strjoin(prompt, branch, &info->prompt_mem);
		if (prompt == NULL)
			ft_error(ERROR99, info);
		prompt = ft_strjoin(prompt, "\001\x1b[34m\002) "WHITE, &info->prompt_mem);
		if (prompt == NULL)
			ft_error(ERROR99, info);
	}
	return (prompt);
}
