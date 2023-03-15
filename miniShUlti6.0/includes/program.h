/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 09:46:26 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/14 06:01:17 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

# include "libft.h"
# include "listft.h"

# define OUTPUT 0
# define INPUT 1
# define TMPFILE "./srcs/.tmp"
# define ANCHOR 0x100
# define ABSOL 0x1
# define RELAT 0x2

typedef struct s_minish
{
	t_node			*paths_list;
	t_node			*argv_list;
	t_node			*env_list;
	t_node			*skipper;
	char			**ft_argv;
	char			**cmd_arr;
	char			**ft_env;
	char			**temp;
	char			*env_to_search;
	char			*temporary;
	char			*input;
	char			*post_input;
	char			*name;
	char			*key;
	char			*value;
	char			*pwd;
	char			*cmd;
	char			s;
	char			*system_path;
	int				len;
	int				n_pipes;
	int				stdin_cpy;
	int				stdout_cpy;
	int				path_flag;
	int				single_q;
	int				double_q;
	int				built_flag;
	int				pipefd[2];
	int				pids[100];
	int				cd_flag;
	unsigned char	*set;
}	t_minish;

void			mini_init(t_minish *minish, char **argv, char **env);
void			set_paths(t_minish *minish);
void			freestr(char *input);
int				get_input(t_minish *minish);
void			input_handler(t_minish *minish);
void			cpychar(t_minish *minish, int i);
void			cpychar_gen(char *str, int i, char **out);
void			expander(t_minish *minish);
int				double_env(t_minish *minish, int i);
int				quotes_to_ignore(t_minish *minish, int i);
unsigned char	*set_builder(void);
char			selector(char *input, unsigned char *set);
void			pre_split(t_minish *minish);
void			post_split(t_minish *minish);
void			tagger(t_minish *minish);
int				append_compare(char *box);
int				builtin_compare(char *box);
int				heredoc_compare(char *box);
int				redir_compare(char *box);
int				pipe_compare(char *box);
void			exec_pipeline(t_minish *minish, pid_t *pid);
void			argv_builder(t_minish *minish);
t_node			**set_argv(t_minish *minish);
void			exit_b(t_minish *minish);
int				permission_denied(t_minish *minish);
void			get_paths(t_minish	*minish);
char			*get_env(t_minish *minish, char	*query);
int				relative_handler(t_minish *minish);
int				absolute_handler(t_minish *minish);
int				exec_command(t_minish *minish);
int				heredoc(t_node *eof, t_minish *minish);
void			redir(t_node *file_node, t_minish *minish);
void			exit_b(t_minish *minish);
void			default_export(t_minish *minish);
int				existence(t_minish *minish);
void			export_var(t_minish *minish);
int				get_flag(char *box, int *f);
void			get_key(t_minish *minish, int f);
void			get_value(t_minish *minish, char *box);
void			case2(t_minish *minish);
void			case1(t_minish *minish);
int				export(t_minish *minish);
int				unset(t_minish *minish);
int				set_cmd_arr(t_minish *minish);
void			shlvl(t_minish *minish);
int				get_dist_from_anchor(t_node *l);
int				cd_b(t_minish *minish);
int				first_blood(t_minish *minish);

#endif
