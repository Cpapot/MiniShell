/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:13:44 by cpapot            #+#    #+#             */
/*   Updated: 2023/06/05 14:53:34 by mgagne           ###   ########.fr       */
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
}					t_commands;

typedef struct s_info
{
	char		*prompt_string;
	char		*lastprompt_string;
	char		**envp;
	char		*tmp_string;
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

typedef struct s_exec
{
	int			final_execstat;
	t_int_list	*fd_list;
	char		*path;
	char		**paths;
	int			fd;
	int			in_fd;
	int			out_fd;
	char		**envp;
	pid_t		*pid_tab;
	t_commands	actual_cmd;
	int			*fd_tab;
	int			end;
}				t_exec;

/*						MINISHELL						*/
void		close_minishell(t_info	*info, int status);

/*						error							*/
void		ft_error(const char *error, t_info *info);

/*						minishell_utils					*/
void		print_error_exit(t_info *info, char *error, int status);
void		print_error(char *error);
char		*ft_getenv(char *env, char **envp, t_memlist **stock);
int			is_char_in_str(char c, const char *str);

/*						parsing							*/
t_commands	*parsing(t_info *info);
int			quote_size_env(char *str, int mode);

/*						split_pipe						*/
t_commands	*split_pipe(t_info *info, t_list *lst);

/*						shell_split						*/
t_list		*shell_split(t_info *info, char *str, t_memlist **stock);

/*						swap_env						*/
void		swap_env(t_list *lst, t_info *info, char **envp);
char		*swap_envstr(char *str, t_info *info, char **envp, int *index);
int			is_contain_env(char *str);
char		*start(char *str, int size, t_info *info);
char		**set_endstartenv(char **parsedenv, t_info *info, int index, \
			int end);
char		*getenv_instr(char *str, int size, t_info *info, char **envp);
char		**empty_tab(t_info *info);

/*						history							*/
void		addto_logs(char *commands, t_info *info);

/*						parsing_redir					*/
t_list		*find_redirection(t_list *lst, t_info *info, int id);
int			is_redirection(char *str);

/*						parsing utils					*/
char		*ft_strndup(const char *s1, size_t n, t_memlist **stock);
void		ft_lstdiradd_back(t_dir **lst, t_dir *new);
t_dir		*ft_lstdirnew(char *type, char *dest, t_memlist **mem);
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
int			bi_export(t_list *lst, t_info *info, int fd);
int			bi_env(t_list *lst, t_info *info, int fd);
int			bi_pwd(t_info *info, int out_fd);
int			bi_cd(t_list *lst, t_info *info);
int			bi_exit(t_list *lst, t_info *info);
int			bi_unset(t_list *lst, t_info *info);

/*						bi_UTILS						*/
void		print_export(char **envp, t_info *info, int fd);
void		print_env(char **envp, int fd);
char		*start(char *str, int size, t_info *info);
char		*find_var(char *str, t_info *info);
char		*find_name(char *str, t_info *info);
int			is_var_already_exist(char *name, char **envp, t_info *info);
int			is_builtins(t_list *lst);

/*						exit_status						*/
char		*swap_exit(char *str, t_info *info, int *index);
void		set_exitstatus(int status);
int			get_exitstatus(void);
void		set_final_exitstatus(int status, t_exec *exec);

/*						signals							*/
void		catch_signals(int sig);
void		catch_signals_child(int sig);
void		catch_signals_heredoc(int sig);
void		catch_signals_backslash(int sig);

/*						prompt							*/
void		prompt(t_info *info);
char		*prompt_string(t_info *info);

/*						execution						*/
void		execution(t_info *info);

/*						exec_pid						*/
int			init_fd_pid(t_info *info, t_exec *exec);
void		wait_close(t_exec *exec, int i);
void		add_pid(t_info *info, t_exec *exec, pid_t pid);

/*						exec_redir						*/
int			redirect(t_info *info, t_exec *exec, t_commands lst_cmd);

/*						exec_utils						*/
char		**get_big_path(t_info *info, char **envp);
int			contains_slash(char *cmd);
char		**cmd_to_tab(t_info *info, t_commands cmd);
char		*get_path(t_info *info, char **path, char *cmd);

/*						exec_invoke						*/
int			handle_command(t_info *info, t_exec *exec, char **cmd);
int			exec_file(t_info *info, t_exec *exec, char **cmd_tab);
void		exec_command(t_info *info, t_exec *exec, int fd[2], char **cmd);

/*							fd							*/
void		add_fd(t_int_list **fd_list, int fd, t_memlist *mem);
void		close_lst(t_int_list *fd);
void		r_fd(t_exec	*exec);
int			empty_pipe(t_exec *exec, t_info *info);

void		printtest(t_info *info);

#endif
