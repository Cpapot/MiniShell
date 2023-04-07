/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:57:30 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/07 16:58:45 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	unset_parsing(char *str, t_list *lst)
{
	int	i;

	i = 0;
	if (str[0] <= '9' && str[0] >= '0')
		break ;
	if (str == NULL || ft_strcmp(str, ""))
		return (2);
	while (str[i])
	{
		if (is_char_in_str(str[i], INV_ID_EXPORT))
			return (1);
		i++;
	}
	if (lst->next != NULL)
		return (1);
	return (0);
}

int	bi_unset(t_list *lst, t_info *info)
{
	int		parsing_res;
	char	*str;
	int		var_pos

	set_exitstatus(0);
	if (lst == NULL)
		return (1);
	str = lst->content;
	parsing_res = unset_parsing(str, lst);
	if (parsing_res == 1)
		return (ft_error(EXPORTERROR1, info), -1);
	if (parsing_res == 2)
		return (1);

}
