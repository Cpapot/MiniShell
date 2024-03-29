/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:23:58 by cpapot            #+#    #+#             */
/*   Updated: 2023/06/05 15:38:28 by mgagne           ###   ########.fr       */
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
	if (sig == SIGINT)
	{
		set_exitstatus(130);
		ft_printf_fd(2, "\n");
	}
	else if (sig == SIGQUIT)
	{
		set_exitstatus(131);
		ft_printf_fd(2, "Quit\n");
	}
}

void	catch_signals_heredoc(int sig)
{
	(void)sig;
	ft_printf_fd(2, "\n");
	exit(1);
}
