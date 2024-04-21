/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 04:34:29 by abquaoub          #+#    #+#             */
/*   Updated: 2024/04/21 17:45:22 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <libgen.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct flags
{
	int		status;
	int		flag;
	int		flag_rediction;
}			flag_t;

typedef struct files
{
	t_list	*outfile;
	t_list	*intfile;

}			files_t;

typedef struct Data
{
	int		status;
	int		fd[2];
	int		in;
	int		out;
	int ex;
	int ex1;
	int red;
	int pid;
	int exec;
}			data_t;
void	ft_nested_pip_ex(t_list *head, char **env, data_t *data , int fd1 , int fd0);
void ft_print_tree(t_list *head);
t_list	*ft_split_linked_pip(char *str ,char c);
t_list * ft_nested_pip(char *line);
t_list	*split_end_or(char *str);
void ft_exec(char *line , char **env, data_t *data);
void		split_line(char **command, t_list **redirec, t_list **cmd);
t_list		*ft_split_command(char *line);
void		ft_print_list(t_list *head);
t_list		*handel_qutes(char *command, char q);
void		ft_close(int fd[][2], int size);
void		ft_display(t_list *ptr);
void		ft_stock_pipe(char *line, t_list **ptr);
void		ft_stock_variables(t_list **head, char **env);
int			ft_check(char *ss);
int			ft_strlen1(char *str);
char		*get_next_line(int fd);
char		*ft_strjoin1(char *s1, char *s2);
void		ft_read_heredoc(char *end, int fd);
char		*ft_read_stdin(char *str);
int			access_intfile(char *path);
int			access_outfile(char *path);
void		ft_echo(char **str);
int			ft_check_script(char *str, char *type);
char		**ft_mini_split(char *str);
int			count_words(char *str);
char		**value(char *str);
int			ft_check(char *str);
void		red(void);
void		cyan(void);
void		yellow(void);
void		ft_print(char **str);
void		reset(void);
void		ft_pwd(int flags, data_t *data);
void		ft_pipe(char *str, char **env, data_t *data);

void		ft_command(char *line, char **env, data_t *data);
t_list		*ft_search_node(t_list *list, char *str);
t_list		*ft_handel_quotes(char *command);
int			ft_cd(char **command, flag_t **flag);
void		ft_free(char **str);
char		*ft_check_command(char *cmd);
char		**ft_handel_dollar(char **cmd);
char		**ft_handel_Tilde(char **command);
int			ft_count_character(char *str, char c);
void		ft_Wildcards(char *cmd);
void		ft_export(char **cmd, t_list **ptr, flag_t *flag);
void		ft_unset_before(t_list **list, char *str);
void		ft_unset(t_list **head, char **command);
void		ft_env(t_list *exp, int out);
void		ft_parse_commnad(char *cmd);
int			ft_count(char **av);
void		ft_exit(char *line);
int			access_outfile_herdoc(char *path);
char		**ft_handel_qutes(char *str);
char		**ft_split_derection(char **command);
int			ft_count_der(char **command);
t_list		*return_command(char *line);
void ren_all_line(char *line , char **env , data_t *data);
#endif
