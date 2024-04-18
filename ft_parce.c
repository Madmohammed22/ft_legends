/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parce.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:11:52 by abquaoub          #+#    #+#             */
/*   Updated: 2024/03/23 13:58:17 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	count_words(char *str)
{
	int		i;
	int		count;
	char	c;

	if (str == NULL)
		return (3);
	i = 0;
	count = 0;
	while (str[i])
	{
		c = str[i];
		if (c == 34 || c == 39)
		{
			while (str[i + 1] != c)
				i++;
			i += 2;
			count++;
		}
		else if (c != ' ' && c != 0)
		{
			while (str[i] != ' ' && str[i])
				i++;
			count++;
		}
		else if (c == ' ')
			i++;
	}
	count++;
	return (count);
}

char	**ft_mini_split(char *str)
{
	int		i;
	int		j;
	int		size;
	char	**words;
	int		word;
	char	c;

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
			words[word] = ft_substr(str, i + 1, j - 1);
			i += 1;
			i += j;
			word++;
		}
		else if (c != ' ' && c != 0)
		{
			j = 0;
			while (str[i + j] != ' ' && str[i + j])
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

void	ft_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void	ft_print_list(t_list *head)
{
	while (head)
	{
		printf("%s\n", (char *)head->content);
		head = head->next;
	}
}