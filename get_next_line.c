/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:15:01 by abquaoub          #+#    #+#             */
/*   Updated: 2024/02/19 09:56:10 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*ft_read(char *str, int fd)
{
	char	*buff;
	char	*save;
	int		i;

	buff = (char *)malloc(1 + 1);
	while (!ft_check(str))
	{
		save = str;
		i = read(fd, buff, 1);
		if (i == -1)
			return (free(buff), free(save), NULL);
		else if (i == 0)
			break ;
		buff[i] = '\0';
		str = ft_strjoin1(save, buff);
		free(save);
	}
	free(buff);
	return (str);
}

static char	*ft_line(char *str)
{
	int		i;
	char	*ss;

	i = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	ss = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		ss[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		ss[i] = str[i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}

char	*get_next_line(int fd)
{
	char	*str;
	char	*line;

	str = NULL;
	if (fd < 0)
		return (NULL);
	str = ft_read(str, fd);
	if (!str)
		return (NULL);
	line = ft_line(str);
	if (!line)
		return (free(str), NULL);
	return (free(str), line);
}
