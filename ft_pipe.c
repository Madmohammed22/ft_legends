
#include "ft_minishell.h"

void	ft_stock_pipe(char *line, t_list **ptr)
{
	int		i;
	int		j;
	char	*command;

	i = 0;
	j = 0;
	while (line[i])
	{
		j = 0;
		while (line[i + j] != '|' && line[i + j] != 0)
			j++;
		if (line[i + j] == '|' || line[i + j] == '\0')
		{
			command = ft_substr(line, i, j);
			ft_lstadd_back(ptr, ft_lstnew(command));
			if (line[i + j] == 0)
				break ;
			i += j;
		}
		i++;
	}
}

void	ft_close(int fd[][2], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

t_list	*ft_split_command(char *line)
{
	char	**split_command;
	t_list	*command;
	int		i;

	if (!line)
		exit(0);
	split_command = ft_split(line, '|');
	command = NULL;
	i = 0;
	while (split_command[i])
	{
		ft_lstadd_back(&command, ft_lstnew(split_command[i]));
		i++;
	}
	return (command);
}

t_list	*ft_join_command_with_list(char *str)
{
	int		i;
	int		count;
	char	*cmd;
	t_list	*head;

	cmd = NULL;
	head = NULL;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|' && (str[i + 1] == '|'))
			cmd = ft_strtrim(ft_substr(str, i - count, count), " ");
		else if (str[i] == '&' && (str[i + 1] == '&'))
			cmd = ft_strtrim(ft_substr(str, i - count, count), " ");
		if (cmd)
		{
			ft_lstadd_back(&head, ft_lstnew(cmd));
			cmd = ft_substr(str, i, 2);
			ft_lstadd_back(&head, ft_lstnew(cmd));
			i += 2;
			count = 0;
			cmd = NULL;
		}
		count++;
		i++;
	}
	cmd = ft_strtrim(ft_substr(str, i - count, count), " ");
	ft_lstadd_back(&head, ft_lstnew(cmd));
	return (head);
}

t_list	*ft_split_linked_pip(char *str, char c, int flag)
{
	int		i;
	int		count;
	t_list	*head;
	int		count_par;

	head = NULL;
	i = 0;
	count_par = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '(')
			count_par++;
		else if (str[i] == ')')
			count_par--;
		if (str[i] == c && str[i + flag] == c && count_par == 0)
		{
			ft_lstadd_back(&head, ft_lstnew(ft_substr(str, i - count, count)));
			// ft_lstadd_back(&head, ft_lstnew("|"));
			i += 2;
			count = 0;
		}
		count++;
		i++;
	}
	ft_lstadd_back(&head, ft_lstnew(ft_substr(str, i - count, count)));
	return (head);
}

void	ft_pipe(char *str, char **env, data_t *data)
{
	int		size;
	int		i;
	t_list	*command;
	int		tmp;
	int		status;

	command = ft_split_linked_pip(str, '|', 0);
	size = ft_lstsize(command);
	data->in = 0;
	data->out = 1;
	data->ex = 0;
	data->ex1 = 0;
	data->red = 0;
	i = 0;
	while (i < size)
	{
		if (i != size - 1)
		{
			pipe(data->fd);
			data->out = data->fd[1];
		}
		else
			data->out = 1;
		ft_command((char *)command->content, env, data);
		data->ex = data->in;
		data->ex1 = data->out;
		if (i != size - 1)
		{
			close(data->fd[1]);
			data->in = data->fd[0];
		}
		i++;
		command = command->next;
	}
	while (1)
	{
		status = wait(&tmp);
		if (status == data->pid)
			data->status = tmp;
		else if (status == -1)
			break ;
	}
	ft_lstclear(&command, free);
}

void	ft_exec(char *line, char **env, data_t *data)
{
	t_list	*command;
	char	*cmd;
	int		flag;

	command = ft_join_command_with_list(line);
	flag = 1;
	while (command)
	{
		cmd = (char *)command->content;
		if (strcmp(cmd, "||") == 0)
		{
			if (data->status == 0)
				flag = 0;
			else
			{
				command = command->next;
				cmd = (char *)command->content;
				flag = 1;
			}
		}
		else if (strcmp(cmd, "&&") == 0)
		{
			if (data->status == 0)
				flag = 1;
			command = command->next;
			cmd = (char *)command->content;
		}
		if (flag == 1)
		{
			ft_pipe(cmd, env, data);
			flag = 0;
		}
		command = command->next;
	}
}

void	ren_all_line(char *line, char **env, data_t *data)
{
	t_list	*command;

	command = return_command(line);
	// ft_display(command);
	while (command)
	{
		if (data->status == 0 && strcmp((char *)command->content, "&&") != 0)
			ft_pipe((char *)command->content, env, data);
		else if (data->status != 0 && strcmp((char *)command->content,
				"||") != 0)
			ft_pipe((char *)command->content, env, data);
		data->out = 1;
		data->in = 0;
		command = command->next;
	}
}

t_list	*return_command(char *line)
{
	int		i;
	int		count;
	t_list	*command;
	char	*cmd;

	i = 0;
	count = 0;
	command = NULL;
	while (line[i])
	{
		if ((line[i] == '&' && line[i + 1] == '&'))
		{
			cmd = ft_substr(line, i - count, count);
			ft_lstadd_back(&command, ft_lstnew(ft_strtrim(cmd, " ")));
			ft_lstadd_back(&command, ft_lstnew("&&"));
			i++;
			count = -1;
		}
		else if ((line[i] == '|' && line[i + 1] == '|'))
		{
			cmd = ft_substr(line, i - count, count);
			ft_lstadd_back(&command, ft_lstnew(ft_strtrim(cmd, " ")));
			ft_lstadd_back(&command, ft_lstnew("||"));
			i++;
			count = -1;
		}
		count++;
		i++;
	}
	cmd = ft_substr(line, i - count, count);
	ft_lstadd_back(&command, ft_lstnew(ft_strtrim(cmd, " ")));
	return (command);
}
