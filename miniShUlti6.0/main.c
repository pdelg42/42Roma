/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:54:33 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/14 06:01:19 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/program.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		;
	if (sig == SIGQUIT)
		;
	if (sig == SIGSTOP)
		;
}

int	main(int argc, char **argv, char **env)
{
	t_minish	minish;
	pid_t		pid;
	int			status;
	int			i;

	mini_init(&minish, argv, env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTSTP, signal_handler);
	while (argc)
	{
		if (get_input(&minish))
		{
			input_handler(&minish);
			expander(&minish);
			argv_builder(&minish);
			if (!first_blood(&minish))
			{
				if (!set_cmd_arr(&minish))
				{
					freematrix(minish.ft_argv, row_counter(minish.ft_argv));
					freematrix(minish.ft_env, row_counter(minish.ft_env));
					relister(&minish.argv_list);
					freecontent(minish.argv_list);
					freelist(&minish.argv_list);
					freestr(minish.pwd);
					continue ;
				}
				exec_pipeline(&minish, &pid);
				if (pid == -1)
					perror("Fork Failed");
				else if (pid == 0)
				{
					status = exec_command(&minish);
					exit (status);
				}
				else
				{
					i = 0;
					while (minish.pids[i])
						waitpid(minish.pids[i++], &status, 0);
				}
				unlink(TMPFILE);
				freematrix(minish.ft_argv, row_counter(minish.ft_argv));
				freematrix(minish.ft_env, row_counter(minish.ft_env));
				freematrix(minish.cmd_arr, row_counter(minish.cmd_arr));
				relister(&minish.argv_list);
				freecontent(minish.argv_list);
				freelist(&minish.argv_list);
				freestr(minish.pwd);
				continue ;
			}
			unlink(TMPFILE);
			dup2(minish.stdout_cpy, STDOUT_FILENO);
			freematrix(minish.ft_argv, row_counter(minish.ft_argv));
			freematrix(minish.ft_env, row_counter(minish.ft_env));
			freecontent(minish.argv_list);
			freelist(&minish.argv_list);
		}
		freestr(minish.pwd);
	}
	freenode(minish.env_list);
	freelist(&minish.env_list);
	freestr((char *)minish.set);
	return (0);
}
