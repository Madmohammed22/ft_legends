/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:16:22 by abquaoub          #+#    #+#             */
/*   Updated: 2024/03/23 13:58:49 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_check1(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return ((int)str[i]);
		i++;
	}
	return (0);
}

char	**value(char *str)
{
	int		check;
	char	**ptr;
	size_t	i;

	check = ft_check1(str);
	ptr = (char **)malloc(sizeof(char *) * 3);
	ptr[2] = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == check)
			break ;
		i++;
	}
	ptr[0] = ft_substr(str, 0, i);
	ptr[1] = ft_substr(str, (unsigned int)i, ft_strlen(str) - i);
	return (ptr);
}

char	**ft_handel_qutes(char *str)
{
	int		i;
	int		j;
	int		size;
	char	**words;
	int		word;
	char	c;
	int		flag;

	flag = 0;
	i = 0;
	size = count_words(str);
	words = (char **)malloc(sizeof(char *) * size);
	word = 0;
	while (str[i])
	{
		c = str[i];
		j = 1;
		if (c == 34 || c == 39)
		{
			while (str[i + j] != c)
				j++;
			if (j == 1 && str[i + j + 1] == 34)
				flag = 1;
			if (j != 1 && flag == 0)
			{
				words[word] = ft_substr(str, i + 1, j - 1);
				i += 1;
				i += j;
				word++;
			}
			else
				i++;
		}
		else if (c != ' ' && c != 0)
		{
			j = 0;
			while (str[i + j] != ' ' && str[i + j] && str[i + j] != 34)
				j++;
			words[word] = ft_substr(str, i, j);
			i += j;
			word++;
		}
		else if (c == ' ')
			i++;
	}
	words[word] = NULL;
	return (words);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_echo(char **words)
{
	int i;
	if (strcmp("echo", words[0]) == 0)
	{
		if (strcmp("-n", words[1]) == 0)
			i = 2;
		else
			i = 1;
		while (words[i])
		{
			if (words[i + 1] != NULL)
				printf("%s ", words[i]);
			else
				printf("%s", words[i]);

			i++;
		}
	}
	printf("\n");
	ft_free(words);
}