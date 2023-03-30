/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:45:39 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/29 16:16:34 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

# define BUILTINS_H
# include "minishell.h"

/*						BUILTINS					*/
int			bi_echo(t_list *lst, int out_fd);
int			bi_export(char *str, t_info *info);
int			bi_env(t_list *lst, t_info *info);
int			bi_pwd(t_info *info, int out_fd);

/*						UTILS						*/
void		print_export(char **envp);
void		print_env(char **envp);
#endif
