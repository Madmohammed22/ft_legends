
// #include "ft_minishell.h"

// int	count_word(char *str)
// {
// 	int		i;
// 	int		count;
// 	char	c;

// 	if (str == NULL)
// 		return (3);
// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		c = str[i];
// 		if (c == 34 || c == 39)
// 		{
// 			while (str[i + 1] != c)
// 				i++;
// 			i += 2;
// 			count++;
// 		}
// 		else if (c != ' ' && c != 0)
// 		{
// 			while (str[i] != ' ' && str[i])
// 				i++;
// 			count++;
// 		}
// 		else if (c == ' ')
// 			i++;
// 	}
// 	count++;
// 	return (count);
// }

// char	*ft_remove_qoutes(char *str)
// {
// 	int		i;
// 	char	*inside;
// 	char	*outside;
// 	char	*qut_be;
// 	char	*qut_af;
// 	int		f;
// 	char	c;

// 	qut_be = NULL;
// 	qut_af = NULL;
// 	i = 0;
// 	inside = NULL;
// 	f = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 34 || str[i] == 39 && f == 0)
// 		{
// 			c = str[i];
// 			if ((c == 34 || c == 39) && f == 0)
// 				qut_be = ft_strjoin(qut_be, &c);
// 		}
// 		while (ft_isdigit(str[i]) == 1 && str[i])
// 		{
// 			f = 1;
// 			c = str[i];
// 			inside = ft_strjoin(inside, &c);
// 			i++;
// 		}
// 		if (str[i] == 34 || str[i] == 39 && f == 1)
// 		{
// 			c = str[i];
// 			if ((c == 34 || c == 39) && f == 0)
// 				qut_af = ft_strjoin(qut_af, &c);
// 		}
// 		i++;
// 	}
// 	return (inside);
// }

// char	**ft_split_exit(char *str)
// {
// 	int		i;
// 	int		j;
// 	int		size;
// 	char	**words;
// 	int		word;
// 	char	c;

// 	i = 0;
// 	size = count_word(str);
// 	words = (char **)malloc(sizeof(char *) * size);
// 	word = 0;
// 	while (str[i])
// 	{
// 		c = str[i];
// 		if (c == 34)
// 		{
// 			j = 1;
// 			while (str[i + j] != c)
// 				j++;
// 			words[word] = ft_substr(str, i, j + 1);
// 			i += 1;
// 			i += j;
// 			word++;
// 		}
// 		else if (c != ' ' && c != 0)
// 		{
// 			j = 0;
// 			while (str[i + j] != ' ' && str[i + j])
// 				j++;
// 			words[word] = ft_substr(str, i, j);
// 			i += j;
// 			word++;
// 		}
// 		else if (c == ' ')
// 			i++;
// 	}
// 	words[word] = NULL;
// 	return (words);
// }

// void	ft_exit(char *line)
// {
// 	char **command = ft_split_exit(line);
// 	printf("%s\n", command[1]);
// 	exit(0);
// 	printf("%s\n", ft_remove_qoutes(command[1]));

// 	// exit(0);
// }