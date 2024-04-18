/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handel_Tidle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:04:59 by abquaoub          #+#    #+#             */
/*   Updated: 2024/02/22 10:12:36 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_handel_Tilde(char *command)
{
	cahr **command = ft_split(command, ' ');
	char *home = getenv("HOME");
	int i = 0;

	while (command[i])
	{
		if (command[i][0] == '~')
			command[i] = ft_strjoin(home, &command[i][1]);
		i++;
	}
}