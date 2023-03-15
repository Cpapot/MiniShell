/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:13:44 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/15 17:38:50 by cpapot           ###   ########.fr       */
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
# include <signal.h>

# define NL			"\n"
# define SP			" "
# define ERROR1		"Cannot Allocate Memory"

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
t_commands	*parsing(t_info *info);

/*						split_pipe						*/
t_commands	*split_pipe(t_info *info, t_list *lst);

/*						shell_split						*/
t_list		*shell_split(char *str, t_memlist **stock);

/*						swap_env						*/
void		swap_env(t_list *lst, t_info *info);

/*						history							*/
void		addto_logs(char *commands, t_info *info);

/*						parsing utils					*/
char		*ft_strndup(const char *s1, size_t n, t_memlist **stock);
void		ft_lstdiradd_back(t_dir **lst, t_dir *new);
t_dir		*ft_lstdirnew(char *type, char *dest, t_memlist **mem);
int			is_redirection(char *str);
char		*prompt_until_char(char c, t_memlist **stock, char *str);

/*						quote						*/
char		*remove_actual_quote(char *str, t_memlist **stock);
void		remove_quote(t_list *lst, t_memlist **stock);
t_list		*remove_empty_node(t_list *lst);
int			quote_size(char *str, int mode);

void		catch_signals(int sig);
#endif
