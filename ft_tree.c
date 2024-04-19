/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:27:06 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/19 21:29:44 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "ft_minishell.h"
typedef struct s_tree
{
    char *data;
    struct s_tree* left;
    struct s_tree* right;
    // t_list * right;
}              t_tree;

void	ft_display1(t_list *ptr)
{
	while (ptr)
	{
		printf("%s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
}

t_list	*split_co(char *str)
{
	int		i;
	int		count;
	char	*cmd;
	t_list	*head;

	cmd = NULL;
	head = NULL;
	i = 0;
	int count_par = 0;
	count = 0;
	while (str[i])
	{
		if(str[i] == '(')
			count_par++;
		else if(str[i] == ')')
			count_par--;
		if (str[i] == '|' && str[i + 1] == '|' && count_par == 0)
			cmd = ft_strtrim(ft_substr(str, i - count, count), " ");
		else if (str[i] == '&' && str[i + 1] == '&' && count_par == 0)
			cmd = ft_strtrim(ft_substr(str, i - count, count), " ");

		if (cmd)
		{
			ft_lstadd_back(&head, ft_lstnew(cmd));
			cmd = ft_substr(str, i , 2);
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

t_tree *ft_creat_three(char *value)
{
    t_tree *new_tree = (t_tree *)malloc(sizeof(t_tree));
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
//   if (root == NULL) return;
//   printf("%s\n", root->data);
//   ft_display1(root->right);
//   if (root->left)
//     printf("\n");
//   ft_preorder_traversal(root->left);
// }


void ft_nested_pip(t_list *head)
{
	t_list *list = NULL;
	char *cmd;
	while(head)
	{
		cmd = (char *)head->content;
		
		if(strcmp(cmd , "||") != 0 && strcmp(cmd , "&&") != 0)
		{
			
		list = ft_split_linked_pip(cmd , '|', 0);
		while(list)
		{
			if(ft_strchr((char *)list->content , '(') != NULL)
				head->content = ft_strdup("()");
			printf("%s\n" , (char *)list->content);
			list = list->next;
		}
		head->prev = list;
			
		// ft_display(head->prev);
		// printf("\n\n\n\n");
		}
		printf("-----------------------------------\n");
		printf("%s\n" , (char *)head->content);
		head = head->next;
		
	}
}

