/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:54:33 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 15:56:46 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/program.h"

int	reset_minish(t_minish *minish)
{
	unlink(TMPFILE);
	dup2(minish->stdout_cpy, STDOUT_FILENO);
	dup2(minish->stdin_cpy, STDIN_FILENO);
	freematrix(minish->ft_argv, row_counter(minish->ft_argv));
	minish->ft_argv = NULL;
	if (minish->ft_env)
		freematrix(minish->ft_env, row_counter(minish->ft_env));
	minish->ft_env = NULL;
	if (!minish->cd_flag && minish->cmd && row_counter(minish->cmd_arr) > 0)
		freematrix(minish->cmd_arr, row_counter(minish->cmd_arr));
	minish->cmd_arr = NULL;
	freecontent(minish->argv_list);
	freelist(&minish->argv_list);
	minish->valid_flag = 1;
	minish->cmd = NULL;
	return (1);
}

void	closer(t_minish *minish)
{
	if (minish->cmd && minish->cmd[0]
		&& WEXITSTATUS(minish->status) == 127)
		fprintf(stderr, ">>>home: %s: command not found\n", minish->cmd);
	if ((minish->status >> 8) == 254)
		minish->cmd = NULL;
	relister(&minish->argv_list);
	reset_minish(minish);
	minish->valid_flag = 1;
	if (!minish->cd_flag)
		freestr(minish->pwd);
	minish->cd_flag = 0;
}

void	sub_main(t_minish *minish)
{
	get_input(minish);
	input_handler(minish);
	expander(minish);
	argv_builder(minish);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		;
	if (sig == SIGSTOP)
		rl_ding();
}

int	main(int argc, char **argv, char **env)
{
	t_minish	minish;
	pid_t		pid;

	mini_init(&minish, argv, env);
	while (argc)
	{
		sub_main(&minish);
		if (!first_blood(&minish) && minish.valid_flag)
		{
			if (!set_cmd_arr(&minish))
				if (reset_minish(&minish))
					continue ;
			exec_pipeline(&minish, &pid);
			core(&minish, &pid);
		}
		else if (!minish.valid_flag)
			fprintf(stderr, "Invalid sintax\n");
		closer(&minish);
	}
	return (0);
}
