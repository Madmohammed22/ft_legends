/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 04:33:37 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/21 17:29:36 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_len_end(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == c && line[i + 1] == c)
		{
			count++;
			i += 2;
		}
		i++;
	}
	count += 2;
	return (count);
}

// char **ft_split_or(char *cmd)
// {

// 	int i = 0;
// 	char **command = malloc(sizeof(char *) * ft_len_end(cmd , '|'));
// 	int count = 0;
// 	int j = 0;
// 	while(cmd[i])
// 	{
// 		if(cmd[i] == '|' && cmd[i + 1] == '|')
// 		{
// 			command[j] = ft_substr(cmd , i - count , count);
// 			i += 2;
// 			count ;
// 		}
// 		count++;
// 		i++;
// 	}
// }

// char ***splits(char *line)
// {
// 	char ***double_cmd = malloc(sizeof(char **) * ft_len_end(line , '&') ) ;

// 	int j = 0;
// 	int i = 0;
// 	while(line[i])
// 	{
// 		if(line[i] == '&' && line[i + 1] == '&')
// 		{
// 			double_cmd[j] =
// 		}
// 		i++;
// 	}

// }

int	main(int ac, char **av, char **env)
{
	char	*line;
	data_t	data;
	t_list	*head;

	head = NULL;
	data.status = 0;
	data.in = 0;
	data.out = 1;
	data.exec = 0;
	(void)av;
	(void)env;
	if (ac != 1)
		return (1);
	while (1)
	{
		ft_pwd(0, &data);
		line = readline(" ");
		if (!line)
		{
			printf("exit\n");
			return (0);
		}
		add_history(line);
		head = ft_nested_pip(line);
		ft_nested_pip_ex(head, env, &data, 1, 0);
	}
	return (0);
}

// int main()
// {
// 	char **command = ft_split("ls" , ' ');
// 	int pid1 , pid2 ;

// 	int fd = open("file" , O_RDWR ,0644);
// 	printf("%d\n" , fd);
// 	pid1 = fork();
// 	if(pid1 == 0)
// 	{
// 		pid2 = fork();
// 		if(pid2 == 0)
// 		{
// 			dup2(fd, 1);
// 			execve("/bin/ls", command, NULL);

// 		}
// 	}
// }
