/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:23:58 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/30 14:12:31 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	catch_signals(int sig)
{
	(void)sig;
	set_exitstatus(130);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	catch_signals_child(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	set_exitstatus(130);
}

void	catch_signals_heredoc(int sig)
{
	(void)sig;
	ft_printf_fd(2, "\n");
	exit(1);
}

void	catch_signals_backslash(int sig)
{
	(void)sig;
	ft_printf_fd(2, "Quit\n");
	set_exitstatus(131);
}
