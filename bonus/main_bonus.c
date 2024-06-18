/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:02:29 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/06/18 18:05:59 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	int	pid;
	t_multi	pipex;

	if (argc < 5)
		return (0);
	create_pipes(&pipex);
	permissions_and_open(argv[1], argv[argc - 1], &pipex);
	pipex.cmd_qty = argc - 3;
	pipex.cmd_i = 0;
	while (pipex.cmd_i < pipex.cmd_qty) //fork all child processes
	{
		pipex.curr = pipex.cmd_i % 2;
		pipex.prev = (pipex.cmd_i + 1) % 2;
		pid = fork();
		if (pid == -1)
			return (error_return("fork"));
		if (pid == 0)
			child_process_bonus(argv, env, &pipex);
		pipex.cmd_i++;
	}
	close(pipex.inf_fd);
	close(pipex.outf_fd);
	close_all_pipes(&pipex);
	wait_loop(&pipex);
	return (0);
}

void	wait_loop(t_multi *pipex)
{
	int 	i;

	i = 0;
	while (i < pipex->cmd_qty)
	{
		wait(NULL);
		i++;
	}
}

void	close_all_pipes(t_multi *pipex)
{
	close(pipex->pipe_fd[0][0]);
	close(pipex->pipe_fd[0][1]);
	close(pipex->pipe_fd[1][0]);
	close(pipex->pipe_fd[1][1]);
}

void	create_pipes(t_multi *pipex)
{
	if (pipe(pipex->pipe_fd[0]) == -1)
		error_return("pipe 0");
	if (pipe(pipex->pipe_fd[1]) == -1)
		error_return("pipe 1");
}

int	child_process_bonus(char **argv, char **env, t_multi *pipex)
{
	char	*cmd_file;
	char	**cmd;

	// close all relevant ends per condition of first last or middle command
	close_selected_pipes(pipex);
	replace_pipes(pipex);
	//close_all_pipes(pipex);
	cmd = ft_split(argv[pipex->cmd_i + 2], ' ');
	cmd_file = find_cmd_file(cmd, env);
	if (cmd_file == NULL)
	{
		free(cmd_file);
		free_array(cmd);
		exit(EXIT_FAILURE);
	}
	execve(cmd_file, cmd, env);
	free_array(cmd);
	return (error_return("execve"));
}

void	replace_pipes(t_multi *pipex)
{
	if (pipex->cmd_i == 0) // first command
	{
		if (dup2(pipex->inf_fd, 0) == -1)
			error_return("dup2 infile");
		if (dup2(pipex->pipe_fd[pipex->curr][1], 1) == -1)
			error_return("dup2 pipe[current][1]");
	}
	else if (pipex->cmd_i == pipex->cmd_qty - 1) //last command
	{
		if (dup2(pipex->pipe_fd[pipex->prev][0], 0) == -1)
				error_return("dup2 pipe[previous][0]");
		if (dup2(pipex->outf_fd, 1) == -1)
				error_return("dup2 outfile");	
	}
	else
	{
		if (dup2(pipex->pipe_fd[pipex->prev][0], 0) == -1)
			error_return("dup2 pipe[previous][0]");
		if (dup2(pipex->pipe_fd[pipex->curr][1], 1) == -1)
			error_return("dup2 pipe[current][1]");
	}
}

void	close_selected_pipes(t_multi *pipex)
{
	if (pipex->cmd_i == 0) // first command
	{
		close(pipex->pipe_fd[pipex->curr][0]);
		close(pipex->pipe_fd[pipex->prev][0]);
		close(pipex->pipe_fd[pipex->prev][1]);
		
	}
	else if (pipex->cmd_i == pipex->cmd_qty - 1) //last command
	{
		if (dup2(pipex->pipe_fd[pipex->prev][0], 0) == -1)
				error_return("dup2 pipe[previous][0]");
		if (dup2(pipex->outf_fd, 1) == -1)
				error_return("dup2 outfile");	
		close(pipex->pipe_fd[pipex->curr][0]);
		close(pipex->pipe_fd[pipex->curr][1]);
		close(pipex->pipe_fd[pipex->prev][1]);
	}
	else
	{
		close(pipex->pipe_fd[pipex->curr][0]);
		close(pipex->pipe_fd[pipex->prev][1]);
	}
}

void	open_files(char *infile, char *outfile, t_multi *pipex)
{
	pipex->inf_fd = open(infile, O_RDONLY);
	pipex->outf_fd = open(outfile, O_WRONLY);
	if (pipex->inf_fd == -1 || pipex->outf_fd == -1)
		error_return("open");
}
