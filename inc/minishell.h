/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:13:44 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/02 15:40:39 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define NL			"\n"

typedef struct s_fd
{
	int	stdout;
	int	stdin;
	int	stderr;
}	t_fd;

typedef struct s_commands
{
	t_list	**command;
	t_fd	fd;
}	t_commands;

typedef struct s_info
{
	char		*prompt_string;
	t_commands	**final_parse;
	t_fd		fd;
	t_memlist	*parsing;
	t_memlist	*lexer;
	t_list		**command;
}	t_info;

/*						minishell_utils					*/
void		print_error(t_info *info, char *error);
void		free_all(t_info *info);

/*						parsing							*/
t_list		**lexer(t_info *info);
t_list		**parsing(t_info *info);

/*						shell_split						*/
char		**shell_split(char *str, t_memlist **stock);

/*						redirection						*/
t_list		*out_redirection(t_list	*lst, int index, t_info *info);
t_list		*in_redirection(t_list	*lst, int index, t_info *info);
t_list	    *out_double_redirection(t_list	*lst, int index, t_info *info);
t_list	    *in_double_redirection(t_list	*lst, int index, t_info *info);

/*						parsing utils					*/


#endif
