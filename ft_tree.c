/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:27:06 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/21 19:58:58 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

typedef struct s_tree
{
	char			*data;
	struct s_tree	*left;
	struct s_tree	*right;
	// t_list * right;
}					t_tree;

void	ft_display1(t_list *ptr)
{
	while (ptr)
	{
		printf("%s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
}

t_list	*split_end_or(char *str)
{
	int		i;
	int		count;
	char	*cmd;
	t_list	*head;
	int		count_par;

	cmd = NULL;
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
		if (str[i] == '|' && str[i + 1] == '|' && count_par == 0)
			cmd = ft_strtrim(ft_substr(str, i - count, count), " ");
		else if (str[i] == '&' && str[i + 1] == '&' && count_par == 0)
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

t_tree	*ft_creat_three(char *value)
{
	t_tree	*new_tree;

	new_tree = (t_tree *)malloc(sizeof(t_tree));
	if (!new_tree)
		return (NULL);
	new_tree->data = value;
	new_tree->left = NULL;
	new_tree->right = NULL;
	return (new_tree);
}

// void ft_create_left_tree(t_tree *parent, char *value)
// {
//     parent->left = ft_creat_three(value);
//     parent->left->right = test(value);
// }
// void ft_preorder_traversal(t_tree* root) {
//   if (root == NULL) return ;
//   printf("%s\n", root->data);
//   ft_display1(root->right);
//   if (root->left)
//     printf("\n");
//   ft_preorder_traversal(root->left);
// }

void	ft_print_tree(t_list *head)
{
	if (!head)
		return ;
	// while (head)
	// {
	ft_display(head);
	// ft_display(head->new_list);
	// head = head->next->next;
	// ft_display(head->new_list);
	// ft_display(head->new_list->new_list);
	// ft_display(head->new_list->new_list->new_list);
	// // ft_print_tree(head->new_list);
	// head = head->next;
	// }
	printf("--------------------------------------------\n");
}

t_list	*ft_nested_pip(char *line)
{
	t_list	*head;
	t_list	*new;
	t_list	*list;
	char	*cmd;

	head = split_end_or(line);
	new = head;
	list = NULL;
	while (head)
	{
		cmd = (char *)head->content;
		if (strcmp(cmd, "||") != 0 && strcmp(cmd, "&&") != 0)
		{
			list = ft_split_linked_pip(cmd, '|');
			head->new_list = list;
			while (list)
			{
				if (ft_strchr((char *)list->content, '(') != NULL)
				{
					list->x = 1;
					list->content = ft_strtrim((char *)list->content, "() |");
					list->new_list = ft_nested_pip((char *)list->content);
				}
				list = list->next;
			}
		}
		else
			head->new_list = NULL;
		head = head->next;
	}
	return (new);
}

void	ft_pipe_x(char *str, char **env, data_t *data)
{
	int		size;
	int		i;
	t_list	*command;
	int		tmp;
	int		status;

	command = ft_split_linked_pip(str, '|');
	size = ft_lstsize(command);
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

void	ft_nested_pip_ex(t_list *head, char **env, data_t *data, int fd1,
		int fd0)
{
	int	tmp;
	int	status;

	data->out = fd1;
	data->in = fd0;
	while (head)
	{
		if (strcmp((char *)head->content, "&&") == 0)
		{
			if (data->status == 0)
			{
				data->out = 1;
				data->in = 0;
				data->exec = 0;
			}
			else
				data->exec = 1;
		}
		else if (strcmp((char *)head->content, "||") == 0)
		{
			if (data->status != 0)
			{
				data->out = 1;
				data->in = 0;
				data->exec = 0;
			}
			else
				data->exec = 1;
		}
		else
		{
			if (data->exec == 0)
			{
				while (head->new_list)
				{
					pipe(data->fd);
					data->out = data->fd[1];
					if (head->new_list->next == NULL)
						data->out = 1;
					if (head->new_list->x == 1)
						ft_nested_pip_ex(head->new_list->new_list, env, data,
							data->out, data->in);
					else
						ft_command((char *)head->new_list->content, env, data);
					close(data->fd[1]);
					data->in = data->fd[0];
					head->new_list = head->new_list->next;
				}
				while (1)
				{
					status = wait(&tmp);
					if (status == data->pid)
						data->status = tmp;
					else if (status == -1)
						break ;
					ft_lstclear(&head->new_list, free);
				}
			}
		}
		head = head->next;
	}
}
