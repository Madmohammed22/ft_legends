/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:54:33 by abquaoub          #+#    #+#             */
/*   Updated: 2024/02/23 18:26:05 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_cd(char **command, flag_t **flag)
{
	command = ft_handel_Tilde(ft_handel_dollar(command));

	if (ft_count(command) <= 2)
	{
		if (access(command[1], F_OK) == 0)
		{
			chdir(command[1]);
			(*flag)->status = 0;
		}
		else
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			(*flag)->status = 1;
		}
	}
	else
	{
		ft_putstr_fd(" too many arguments\n", 2);
		(*flag)->status = 1;
	}

	return (0);
}