/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:29:28 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/14 20:42:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_ms	*ms;

	if (ac == 1)
	{
		(void)av;
		ms = init_program(env);
		the_program(ms);
		free(ms);
	}
	else
		ft_putstr_fd("Arguments aren't allowed\n", 2);
	return (0);
}