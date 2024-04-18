/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:56:16 by abquaoub          #+#    #+#             */
/*   Updated: 2024/02/24 17:53:31 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_handl_qutes(char *str)
{
	int		i;
	char	*ptr;

	i = 1;
	if (str[0] == 32)
	{
		while (str[i] && str[i] != 34)
			i++;
		ptr = malloc(sizeof(char) * i);
		i = 0;
		while (str[i + 1] && str[i + 1] != 34)
		{
			ptr[i] = str[i + 1];
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (ft_strdup(str));
}

int	ft_parce_str(char *str, int flag)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	if (ft_isalpha(str[i]) == 0)
		return (1);
	while (str[i])
	{
		if ((ft_isalpha(str[i]) == 1 || ft_isdigit(str[i]) == 1)
			|| (str[i] == '+' && str[i + 1] && flag == 1))
			i++;
		else
			return (1);
	}
	return (0);
}

void	ft_export(char **cmd, t_list **ptr, flag_t *flag)
{
	int count = 0;
	char **command;
	char *str = ft_strdup("");
	int i = 1;
	while (cmd[i])
	{
		command = ft_split(cmd[i], '=');
		if (ft_parce_str(command[0], ft_count(command) - 1) == 0)
		{
			if (ft_strchr(cmd[i], '=') != NULL)
			{
				ft_lstadd_back(ptr, ft_lstnew(cmd[i]));
			}
			count++;
		}
		str = ft_strdup(" not a valid identifier");
		i++;
	}
	if (i - 1 == count)
		flag->status = 0;
	else
	{
		ft_putstr_fd(str, 2);
		flag->status = 1;
	}
}