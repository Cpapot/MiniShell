/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:13:44 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/12 16:03:54 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include "error.h"
# include "exec.h"

# define INV_ID_EXPORT	" !#$%&()*+-.<>=:;`/\'\"@{}[]^|~\n? "
# define INVID			" !#$%&()*+-.<>=:;`/\'\"@{}[]^|~\n"
# define NL				"\n"
# define SP				" "

typedef struct s_envp
{
	char			*name;
	char			*var;
	struct s_envp	*next;
}	t_envp;

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
	t_memlist	*prompt_mem;
	t_memlist	*final_memparse;
	t_memlist	*envp_mem;
	t_memlist	*shell_mem;
	int			com_count;
	int			is_finish;
	t_list		**command;
}	t_info;

/*						MINISHELL						*/
void		close_minishell(t_info	*info, int status);

/*						error							*/
void		ft_error(const char *error, t_info *info);

/*						minishell_utils					*/
void		print_error_exit(t_info *info, char *error, int status);
void		print_error(char *error);
void		free_all(t_info *info);
char		*ft_getenv(char *env, char **envp, t_memlist **stock);
int			is_char_in_str(char c, const char *str);

/*						parsing							*/
t_commands	*parsing(t_info *info);

/*						split_pipe						*/
t_commands	*split_pipe(t_info *info, t_list *lst);

/*						shell_split						*/
t_list		*shell_split(t_info *info, char *str, t_memlist **stock);

/*						swap_env						*/
void		swap_env(t_list *lst, t_info *info, char **envp);

/*						history							*/
void		addto_logs(char *commands, t_info *info);

/*						execution						*/
void		execution(t_info *info);

/*						parsing utils					*/
char		*ft_strndup(const char *s1, size_t n, t_memlist **stock);
void		ft_lstdiradd_back(t_dir **lst, t_dir *new);
t_dir		*ft_lstdirnew(char *type, char *dest, t_memlist **mem);
int			is_redirection(char *str);
char		*prompt_until_char(char c, t_memlist **stock, char *str);

/*						quote							*/
char		*remove_actual_quote(char *str, t_memlist **stock);
void		remove_quote(t_list *lst, t_memlist **stock);
t_list		*remove_empty_node(t_list *lst);
int			quote_size(char *str, int mode);
int			quote_size_shellsplit(char *str, int mode);


/*						check_error						*/
int			is_line_valid(t_list *lst, t_info *info);
int			is_command_line(t_list *lst, t_info *info);

/*						BUILTINS						*/
int			find_builtins(t_list *lst, t_info *info, int out_fd);
int			bi_echo(t_list *lst, int out_fd);
int			bi_export(t_list *lst, t_info *info);
int			bi_env(t_list *lst, t_info *info);
int			bi_pwd(t_info *info, int out_fd);
int			bi_cd(t_list *lst, t_info *info);
int			bi_exit(t_list *lst, t_info *info);
int			bi_unset(t_list *lst, t_info *info);

/*						bi_UTILS						*/
void		print_export(char **envp, t_info *info);
void		print_env(char **envp);
char		*start(char *str, int size, t_info *info);
char		*find_var(char *str, t_info *info);
char		*find_name(char *str, t_info *info);
int			is_var_already_exist(char *name, char **envp, t_info *info);

/*						exit_status						*/
char		*swap_exit(char *str, t_info *info);
void		set_exitstatus(int status);

void		catch_signals(int sig);

/*						prompt							*/
void		prompt(t_info *info);
char		*prompt_string(t_info *info);

void		printtest(t_info *info);

#endif
