/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handel_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 00:31:39 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/14 14:54:48 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*return_string(char c)
{
	char	*arr;

	arr = malloc(2);
	arr[0] = c;
	arr[1] = '\0';
	return (arr);
}

t_list	*ft_handel_quotes(char *command)
{
	t_list	*list;
	int		count;
	char	*join;
	int		i;
	int		c;

	list = NULL;
	count = 0;
	join = NULL;
	i = 0;
	c = 0;
	while (command[i])
	{
		if ((command[i] == 34 || command[i] == 39) && !count)
			c = command[i];
		if (command[i] == c)
		{
			count++;
			if (count % 2 == 0)
				count = 0;
			if ((command[i] == c && command[i + 1] == c && count == 1))
			{
				join = ft_strdup("");
				i++;
				count = 0;
			}
		}
		else if ((command[i] == ' ' && count % 2 == 0))
		{
			if (join)
			{
				ft_lstadd_back(&list, ft_lstnew(join));
				count = 0;
			}
			join = NULL;
		}
		else
			join = ft_strjoin(join, return_string(command[i]));
		i++;
	}
	if (join)
		ft_lstadd_back(&list, ft_lstnew(join));
	return (list);
}
