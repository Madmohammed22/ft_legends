/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 06:50:29 by abquaoub          #+#    #+#             */
/*   Updated: 2024/02/24 17:30:12 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_list	*ft_search_node(t_list *head, char *str)
{
	t_list	*node_next;
	char	**var;

	node_next = head;
	while (head)
	{
		var = ft_split((char *)head->content, '=');
		if (strcmp(var[0], str) == 0)
			break ;
		node_next = head;
		head = head->next;
	}
	return (node_next);
}

void	ft_unset_before(t_list **list, char *str)
{
	t_list	*head;
	t_list	*before_node;
	int		flag;
	char	**var;

	head = *list;
	before_node = ft_search_node(head, str);
	flag = 0;
	while (head)
	{
		var = ft_split((char *)head->content, '=');
		if (strcmp(var[0], str) == 0)
		{
			flag = 1;
			break ;
		}
		head = head->next;
	}
	if (flag == 1)
	{
		head = head->next;
		before_node->next = head;
	}
}

void	ft_unset(t_list **head, char **command)
{
	int	i;

	i = 1;
	while (command[i])
	{
		ft_unset_before(head, command[i]);
		i++;
	}
}
