/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 04:33:37 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/18 21:04:03 by abquaoub         ###   ########.fr       */
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

	data.status = 0;
	data.in = 0;
	data.out = 1;
	(void)av;
	if (ac != 1)
		return (1);
	while (1)
	{
		ft_pwd(0, &data);
		line = readline(" ");
		add_history(line);
		ft_exec(line, env, &data);
		// void ft_exec(line , char **env, data_t *data)
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
