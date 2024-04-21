/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:14:52 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/21 19:59:18 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_script(char *str, char *type)
{
	if (strcmp(type, ft_strrchr(str, '.')) == 0)
		return (0);
	return (1);
}

char	*ft_check_command(char *command)
{
	char	*env_path;
	char	*path;
	char	*cmd;
	char	**bins;
	int		i;

	env_path = getenv("PATH");
	bins = ft_split(env_path, ':');
	i = 0;
	while (bins[i])
	{
		path = ft_strjoin(bins[i], "/");
		cmd = ft_strjoin(path, command);
		if (access(cmd, F_OK) == 0)
			return (ft_free(bins), free(path), cmd);
		free(path);
		free(cmd);
		i++;
	}
	ft_free(bins);
	return (NULL);
}

int	ft_count(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	ft_count_character(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	**ft_handel_Tilde(char **command)
{
	int		i;
	char	**new_command;
	char	*path_tilde;

	i = 0;
	new_command = (char **)malloc(sizeof(char *) * (ft_count(command) + 1));
	path_tilde = getenv("HOME");
	while (command[i])
	{
		if (command[i][0] == '~')
			new_command[i] = ft_strjoin(path_tilde, &command[i][1]);
		else
			new_command[i] = ft_strdup(command[i]);
		i++;
	}
	new_command[i] = NULL;
	return (ft_free(command), new_command);
}

char	**ft_handel_dollar(char **command)
{
	int		i;
	char	*var;
	char	**new_split;

	i = 0;
	new_split = (char **)malloc(sizeof(char *) * (ft_count(command) + 1));
	while (command[i])
	{
		var = getenv(&command[i][1]);
		if (var != NULL)
			new_split[i] = ft_strdup(var);
		else
			new_split[i] = ft_strdup(command[i]);
		i++;
	}
	new_split[i] = NULL;
	ft_free(command);
	return (new_split);
}

int	ft_build(char **command, t_list *list, flag_t *flag, int out)
{
	// dup2(out , 1);
	if (command[0] == NULL)
		return (0);
	if (strcmp(command[0], "echo") == 0 && strcmp(command[1], "$?") == 0)
		printf("%d\n", flag->status);
	else if (strcmp(command[0], "echo") == 0)
		ft_echo(command);
	else if (strcmp(command[0], "export") == 0)
		ft_export(command, &list, flag);
	else if (strcmp(command[0], "env") == 0)
		ft_env(list, out);
	else if (strcmp(command[0], "cd") == 0)
		ft_cd(command, &flag);
	// else if (strcmp(command[0], "pwd") == 0)
	// 	ft_pwd(3);
	else if (strcmp(command[0], "exit") == 0)
		return (exit(ft_atoi(command[1])), 0);
	else if (strcmp(command[0], "unset") == 0)
		ft_unset(&list, command);
	else
		return (1);
	return (0);
}

void	split_line(char **command, t_list **redirec, t_list **cmd)
{
	char	*join;
	char	*join_command;
	int		i;

	i = 0;
	while (command[i])
	{
		if (strcmp(command[i], ">>") == 0 || strcmp(command[i], ">") == 0
			|| strcmp(command[i], "<<") == 0 || strcmp(command[i], "<") == 0)
		{
			if (strcmp(command[i], "<<") == 0 || strcmp(command[i], "<") == 0
				|| strcmp(command[i], ">>") == 0 || strcmp(command[i],
					">") == 0)
			{
				join = ft_strjoin(command[i], " ");
				join_command = ft_strjoin(join, command[i + 1]);
				ft_lstadd_back(redirec, ft_lstnew(join_command));
				i++;
			}
		}
		else
			ft_lstadd_back(cmd, ft_lstnew(command[i]));
		i++;
	}
}

void	ft_display(t_list *ptr)
{
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	while (ptr)
	{
		if (strcmp((char *)ptr->content, "||") != 0
			&& strcmp((char *)ptr->content, "&&") != 0)
			printf("%s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void	ft_outfile(t_list *ptr, data_t *data)
{
	char	**split;
	int		outfile;
	int		intfile;
	int		fd[2];

	outfile = data->out;
	intfile = data->in;
	pipe(fd);
	if (ptr == NULL)
		return ;
	while (ptr)
	{
		split = ft_split((char *)ptr->content, ' ');
		if (strcmp(split[0], ">>") == 0)
			outfile = access_outfile_herdoc(split[1]);
		else if (strcmp(split[0], ">") == 0)
			outfile = access_outfile(split[1]);
		else if (strcmp(split[0], "<") == 0)
			intfile = access_intfile(split[1]);
		else if (strcmp(split[0], "<<") == 0)
		{
			ft_read_heredoc(ft_strjoin(split[1], "\n"), fd[1]);
			close(fd[1]);
			intfile = fd[0];
		}
		ptr = ptr->next;
	}
	if (intfile == 0 || outfile == 0)
	{
		data->red = 1;
		printf("bash: %s: Permission denied\n", split[1]);
		data->in = data->ex;
		data->out = data->ex1;
		return ;
	}
	else
		data->in = intfile;
	data->out = outfile;
}

char	**split_string(char *str)
{
	int		i;
	int		count;
	int		j;
	char	**command;
	int		w;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<'))
		{
			if (str[i + 1] == str[i])
				count++;
		}
		else if (!(str[i] == '>' || str[i] == '<') && (str[i + 1] == '>'
				|| str[i + 1] == '<' || !str[i + 1]))
			count++;
		i++;
	}
	i = 0;
	command = malloc((count + 1) * sizeof(char *));
	command[count] = NULL;
	w = 0;
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<'))
		{
			j = 0;
			while (str[i + j] == '<' || str[i + j] != '>')
			{
				command[w][j] = str[i + j];
				j++;
			}
			i += j;
		}
		else
		{
			j = 0;
			while ((str[i + j] != '<' || str[i + j] != '>') && str[i + j])
			{
				command[w][j] = str[i + j];
				j++;
			}
			i += j;
		}
		w++;
	}
	// exit(0);
	// printf("hello");
	return (command);
}

// char **split_redirection(char **command)
// {
// 	int i = 0;
// }

char	**create_command(t_list *head)
{
	int		i;
	int		size;
	char	**command;

	i = 0;
	size = ft_lstsize(head) + 1;
	command = (char **)malloc(sizeof(char *) * size);
	while (head)
	{
		command[i] = ft_strdup((char *)head->content);
		i++;
		head = head->next;
	}
	command[i] = NULL;
	ft_lstclear(&head, free);
	return (command);
}

void	ft_command(char *line, char **env, data_t *data)
{
	char	*cmd;
	char	**command;
	t_list	*handel_quotes;

	handel_quotes = ft_handel_quotes(line);
	command = create_command(handel_quotes);
	cmd = ft_check_command(command[0]);
	if (cmd)
	{
		data->pid = fork();
		if (data->pid == 0)
		{
			dup2(data->in, 0);
			dup2(data->out, 1);
			execve(cmd, command, env);
			perror("execve failing");
		}
	}
	else
	{
		data->status = 127;
		// printf("Error (Wa Tga3d a Regragui)\n");
		printf("Command '%s' not found.\n", command[0]);
	}
	ft_free(command);
}
