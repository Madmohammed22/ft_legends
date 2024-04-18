/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:05:10 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/16 15:05:37 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_pipe(t_list *command, char **env, data_t *data)
{
	int size;
	int i;

	size = ft_lstsize(command);
	i = 0;
	data->in = 0;
	data->out = 1;
	while (i < size)
	{
		if (i != size - 1)
		{
			pipe(data->fd);
			data->out = data->fd[1];
		}
		else
			data->out = 1;
		ft_command((char *)command->content, env, data);
		if (i != size - 1)
		{
			close(data->fd[1]);
			data->in = data->fd[0];
		}
		i++;
		command = command->next;
	}
	ft_lstclear(&command, free);
}