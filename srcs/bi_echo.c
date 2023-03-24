/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:09:34 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/24 17:22:24 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	while (us1[i] != '\0' && us2[i] != '\0' && i < n)
	{
		if (us1[i] != us2[i])
			return (us1[i] - us2[i]);
		i++;
	}
	if (i < n)
		return (us1[i] - us2[i]);
	return (0);
}


int	check_flag(char *str)
{
	int	i;

	if (ft_strncmp(str, "-n", 2) == 0)
	{
		i = 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

void	echo(t_list *lst, int out_fd)
{
	int	i;
	int	is_nl;

	is_nl = 1;
	while (lst && check_flag(lst->content))
	{
		is_nl = 0;
		lst = lst->next;
	}
	while (lst)
	{
		printf( "%s", lst->content);
		lst = lst->next;
		if (lst)
			printf(" ");
	}
	if (is_nl == 1)
		printf( "\n");
	return ;
}
