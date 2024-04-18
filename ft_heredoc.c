/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:51:01 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/15 12:34:40 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_stock_variables(t_list **head, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back(head, ft_lstnew(env[i]));
		i++;
	}
}

void	ft_read_heredoc(char *end, int fd)
{
	char *buff;
	char *join = NULL;
	char *save;
	ft_putchar_fd('>', 0);
	while ((buff = get_next_line(0)) != NULL)
	{
		save = join;
		if (strcmp(end, buff) == 0)
			return ;
		ft_putstr_fd(buff, fd);
		free(save);
		ft_putchar_fd('>', 0);
	}
}