/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:47:02 by codespace         #+#    #+#             */
/*   Updated: 2024/10/28 01:20:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_manager(t_ms *ms, int x)
{
	close(ms->pipefd[1]);
	if (x > 0)
		close(ms->previous_fd);
	ms->previous_fd = ms->pipefd[0];
}

int	bb_executioner(t_ms *ms)
{
	int	v_ret;

	v_ret = 0;
	if (builtins_checker(ms) == 0)
	{
		ms->pid[0] = fork();
		if (ms->pid[0] == -1)
			exit(1);
		signal(SIGQUIT, ft_sigquit_child);
		signal(SIGINT, sigint_here_doc);
		if (ms->pid[0] == 0)
		{
			ft_open_files(ms);
			exit(0);
		}
		v_ret = mini_builtins(ms);
		return (waiting_(ms, v_ret));
	}
	return (v_ret);
}

int	executioner(t_ms *ms)
{
	int			x;
	t_cmdline	*head;

	x = 0;
	head = ms->cmdlines;
	while (ms->cmdlines)
	{
		pipe(ms->pipefd);
		ms->pid[x] = fork();
		if (ms->pid[x] == -1)
			exit(1);
		signal(SIGQUIT, ft_sigquit_child);
		signal(SIGINT, sigint_here_doc);
		if (ms->pid[x] == 0)
			child_process(ms);
		else
			fd_manager(ms, x);
		ms->cmdlines = ms->cmdlines->next;
		x++;
	}
	ms->cmdlines = head;
	return (wait_da_boy(ms));
}

int	executor(t_ms *ms)
{
	int	v_return;

	v_return = 0;
	ms->envi = the_env(ms->env);
	if (ms->envi == NULL)
	{
		ft_putstr_fd("Error: couldn't allocate memory\n", 2);
		return (1);
	}
	the_cmdlines(ms);
	ms->c_count = cmdlines_counter(ms->cmdlines);
	ms->pid = malloc(sizeof(int) * ms->c_count);
	if (!ms->pid)
		return (ft_putstr_fd("Error : malloc failed", 2), 1);
	if (ms->c_count == 1)
		v_return = bb_executioner(ms);
	if (ms->b == false)
		v_return = executioner(ms);
	clear_cmdlines(&ms->cmdlines);
	ft_free_tab(ms->envi);
	free(ms->pid);
	close(ms->pipefd[0]);
	close(ms->pipefd[1]);
	return (v_return);
}
