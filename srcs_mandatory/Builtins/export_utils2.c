/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:59:34 by acarpent          #+#    #+#             */
/*   Updated: 2024/10/28 16:52:51 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_error(char *str)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (NULL);
}

t_env	*init_exp_node(char *name, char *value, int equal_sign)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
	{
		ft_putstr_fd("Error: failed to allocate memory for new env\n", 2);
		return (NULL);
	}
	new_env->equal_sign = equal_sign;
	new_env->name = name;
	if (value)
		new_env->value = value;
	else if (!value && new_env->equal_sign == 1)
		new_env->value = ft_strdup("\"\"");
	else
		new_env->value = NULL;
	new_env->next = NULL;
	new_env->prev = NULL;
	return (new_env);
}

void	add_new(t_env **env, char *name, char *value, int equal_sign)
{
	t_env	*new_env;
	t_env	*last_env;

	if (env == NULL)
		return ;
	new_env = init_exp_node(name, value, equal_sign);
	if (!new_env)
		return ;
	if (*env == NULL)
	{
		*env = new_env;
		new_env->prev = NULL;
	}
	else
	{
		last_env = find_lastv(*env);
		last_env->next = new_env;
		new_env->prev = last_env;
	}
}

char	*find_value(char *str, char *val)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	if (str[i] != '\0' && str[i + 1] != '\0')
	{
		i++;
		j = i;
		while (str[i])
			i++;
		val = ft_substr(str, j, i - j);
	}
	return (val);
}
