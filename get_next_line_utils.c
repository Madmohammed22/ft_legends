/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:19:59 by abquaoub          #+#    #+#             */
/*   Updated: 2024/02/19 09:55:31 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_check(char *ss)
{
	int	i;

	i = 0;
	while (ss && ss[i] != '\0')
	{
		if (ss[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (0);
	}
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	res = (char *)malloc(ft_strlen1(s1) + ft_strlen1(s2) + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1 != NULL)
	{
		while (s1[j] != '\0')
		{
			res[j] = s1[j];
			j++;
		}
	}
	while (s2[i] != '\0')
	{
		res[i + j] = s2[i];
		i++;
	}
	res[i + j] = '\0';
	return (res);
}
