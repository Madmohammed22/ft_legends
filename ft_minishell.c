/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 04:33:37 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/24 15:53:00 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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

int	main(int ac, char **av, char **env)
{
	char	*line;
	data_t	data;
	t_list	*head;

	printf("%d\n", getpid());
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
			return (1);
		}
		add_history(line);
		head = ft_nested_pip(line);
		ft_print_tree(head);

		// ft_display(head);
		// ft_nested_pip_ex(head, env, &data, STDOUT_FILENO, STDIN_FILENO);
	}
	return (0);
}

// int main()
// {
// 	int pid;
// 			char s[100];
// 	pid = fork();
// 	if(pid == 0)
// 	{

// 			printf("%s\n", getcwd(s, 100));

//     // using the command
//     chdir("..");

//     // printing current working directory
//     printf("%s\n", getcwd(s, 100));
// 	}
// 	wait(NULL);
//     printf("--%s\n", getcwd(s, 100));

//     // printing current working directory

// }