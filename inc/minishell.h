/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:13:44 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/08 17:30:01 by cpapot           ###   ########.fr       */
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
# define SP			" "

typedef struct s_dir
{
	char			*type;
	char			*dest;
	struct s_dir	*next;
}					t_dir;

typedef struct s_commands
{
	t_list	*command;
	t_dir	*dir;
}	t_commands;

typedef struct s_info
{
	char		*prompt_string;
	t_commands	*final_parse;
	t_memlist	*parsing;
	t_memlist	*lexer;
	int			tmp;
	t_list		**command;
}	t_info;

/*						minishell_utils					*/
void		print_error(t_info *info, char *error);
void		free_all(t_info *info);

/*						parsing							*/
t_list		**lexer(t_info *info);
t_commands	*parsing(t_info *info);

/*						split_pipe						*/
t_commands	*split_pipe(t_info *info, t_list *lst);

/*						shell_split						*/
t_list		*shell_split(char *str, t_memlist **stock);

/*						redirection						*/
t_list		*out_redirection(t_list	*lst, int index, t_info *info);
t_list		*in_redirection(t_list	*lst, int index, t_info *info);
t_list		*out_double_redirection(t_list	*lst, int index, t_info *info);
t_list		*in_double_redirection(t_list	*lst, int index, t_info *info);

/*						quote							*/
t_list		*regroup_quote(t_list	*lst, t_info *info);

/*						parsing utils					*/
char		*ft_strndup(const char *s1, size_t n, t_memlist **stock);
void		ft_lstdiradd_back(t_dir **lst, t_dir *new);
t_dir		*ft_lstdirnew(char *type, char *dest, t_memlist **mem);

#endif
