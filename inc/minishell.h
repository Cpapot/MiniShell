/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:13:44 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/24 16:12:59 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_info
{
	char		*prompt_string;
	t_memlist	*parsing;
	t_memlist	*lexer;
	t_list		**command;
	t_list		**final;
}	t_info;

/*						minishell_utils					*/
void		print_error(t_info *info, char *error);
void		free_all(t_info *info);

/*						parsing							*/
t_list		**lexer(t_info *info);

/*						shell_split						*/
char		**shell_split(char *str, t_memlist **stock);

/*						parsing utils					*/

#endif
