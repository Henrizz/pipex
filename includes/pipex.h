/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Henriette <Henriette@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:02:55 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/05/12 21:41:09 by Henriette        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft_rep/libft.h"
# include "../42_rep/printf/libftprintf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int	check_permissions(char *infile, char *outfile);
int	error_return(char *message);
void	free_array(char **str);
int	child_process(char **argv, char **env, int *pipe_fd);
int	parent_process(char **argv, char **env, int *pipe_fd, int pid);
char	*find_cmd_file(char **cmd, char **env);
char	*get_paths(char **env, char *name);

#endif
