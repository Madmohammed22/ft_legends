/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:54:33 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/23 22:11:37 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_cd(char **command)
{
	command = ft_handel_Tilde(ft_handel_dollar(command));

	if (ft_count(command) <= 2)
	{
		if (access(command[1], F_OK) == 0)
		{
			chdir(command[1]);
		}
		else
			ft_putstr_fd(" No such file or directory\n", 2);
	}
	else
		ft_putstr_fd(" too many arguments\n", 2);

	return (0);
}