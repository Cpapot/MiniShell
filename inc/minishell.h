/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:13:44 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/30 15:59:28 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "error.h"
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

# define INV_ID_EXPORT	" !#$%&()*+-.<>=:;`/\'\"@{}[]^|~\n?"
# define INVID			" !#$%&()*+-.<>=:;`/\'\"@{}[]^|~\n"
# define NL				"\n"
# define SP				" "

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
	char		*lastprompt_string;
	char		**envp;
	t_commands	*final_parse;
	t_memlist	*exec_mem;
	t_memlist	*parsing;
	t_memlist	*final_memparse;
	t_memlist	*envp_mem;
	int			com_count;
	int			is_finish;
	t_list		**command;
	char		*path;
}	t_info;

/*						MINISHELL						*/
void		close_minishell(t_info	*info);

/*						minishell_utils					*/
void		print_error_exit(t_info *info, char *error);
void		print_error(char *error);
void		free_all(t_info *info);
char		*ft_getenv(char *env, char **envp, t_memlist **stock);
int			is_char_in_str(char c, const char *str);

/*						parsing							*/
t_commands	*parsing(t_info *info);

/*						split_pipe						*/
t_commands	*split_pipe(t_info *info, t_list *lst);

/*						shell_split						*/
t_list		*shell_split(char *str, t_memlist **stock);

/*						swap_env						*/
void		swap_env(t_list *lst, t_info *info, char **envp);

/*						history							*/
void		addto_logs(char *commands, t_info *info);

/*						execution						*/
//void		execution(t_info *info, char **envp);

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

/*						check_error					*/
int			is_line_valid(t_list *lst);
int			is_command_line(t_list *lst);


/*						BUILTINS					*/
int			bi_echo(t_list *lst, int out_fd);
int			bi_export(char *str, t_info *info);
int			bi_env(t_list *lst, t_info *info);
int			bi_pwd(t_info *info, int out_fd);
int			bi_cd(t_list *lst, t_info *info);

/*						UTILS						*/
void		print_export(char **envp);
void		print_env(char **envp);

void		catch_signals(int sig);

void		printtest(t_info *info);

#endif
