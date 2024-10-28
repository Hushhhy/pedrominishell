/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_backslash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:07:23 by acarpent          #+#    #+#             */
/*   Updated: 2024/10/25 17:12:00 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigquit_handler(int sig)
{
	(void)sig;
	g_var = CTRL_BS;
}

void	ft_sigquit_child(int sig)
{
	(void)sig;
	g_var = CTRL_BS;
	ft_putstr_fd("Quit (core dumped)", 2);
	printf("\n");
}

void	ft_sigquit_setup(void)
{
	struct sigaction	sa_quit;

	sa_quit.sa_handler = ft_sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}