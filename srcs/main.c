/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Henriette <Henriette@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:02:29 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/05/12 21:42:02 by Henriette        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	pid;
	int	pipe_fd[2];

	i = 0;
	if (argc != 5)
		return (0);
	if (!check_permissions(argv[1], argv[4]))
		return (0);
	if (pipe(pipe_fd) == -1)
		return (error_return("pipe: "));
	pid = fork();
	if (pid == 0)
	{
		child_process(argv, env, pipe_fd);
	}
	else 
	{
		parent_process(argv, env, pipe_fd, pid);
	}
	return (0);
}

int	parent_process(char **argv, char **env, int *pipe_fd, int pid)
{
	int	fd;
	char	*cmd_file;
	char	**cmd;
	
	close(pipe_fd[1]);
	fd = open(argv[4], O_WRONLY);
	if (fd == -1)
		return (error_return("open outfile: "));
	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	cmd = ft_split(argv[3], ' ');
	cmd_file = find_cmd_file(cmd, env);
	if (cmd_file == NULL)
	{
		free(cmd_file);
		exit(EXIT_FAILURE);
	}	
	waitpid(pid, NULL, 0);
	execve(cmd_file, cmd, env);
	free(cmd);
	return (0);
}

int	child_process(char **argv, char **env, int *pipe_fd)
{
	char	*cmd_file;
	char	**cmd;
	//int	i = 0;
	int	fd;

	close(pipe_fd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (error_return("open infile: "));
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	cmd = ft_split(argv[2], ' ');
	cmd_file = find_cmd_file(cmd, env);
	if (cmd_file == NULL)
	{
		free(cmd_file);
		exit(EXIT_FAILURE);
	}	
	execve(cmd_file, cmd, env);
	free(cmd);
	return (0);
}

