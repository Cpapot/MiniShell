/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:45:39 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/26 19:13:55 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

# define BUILTINS_H
# include "minishell.h"

/*						BUILTINS					*/
void		bi_echo(t_list *lst, int out_fd);
int			bi_export(char *str, t_info *info);

#endif
