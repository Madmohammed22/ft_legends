/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 06:48:15 by abquaoub          #+#    #+#             */
/*   Updated: 2024/02/24 17:50:32 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_env(t_list *exp, int out)
{
	dup2(out, 1);
	while (exp)
	{
		printf("%s\n", (char *)exp->content);
		exp = exp->next;
	}
}