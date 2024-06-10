/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:41:49 by hzimmerm          #+#    #+#             */
/*   Updated: 2024/06/10 11:25:18 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	new_line_check(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_excerpt_line(char *temp)
{
	int		i;
	char	*line;

	i = 0;
	if (!temp[i])
		return (NULL);
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	line = (char *)ft_calloc((i + 1 + (new_line_check(temp))), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] != 0 && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*keep_rest(char *temp)
{
	int		i;
	int		j;
	char	*new_temp;

	i = 0;
	j = 0;
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	if (temp[i] == '\0')
	{
		free(temp);
		return (NULL);
	}
	new_temp = (char *)ft_calloc((ft_strlen(temp) - i + 1), sizeof(char));
	if (!new_temp)
	{
		free(temp);
		return (NULL);
	}
	i++;
	while (temp[i] != '\0')
		new_temp[j++] = temp[i++];
	new_temp[j] = '\0';
	free(temp);
	return (new_temp);
}

char	*get_next_line(int fd)
{
	static char	*temp[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (temp[fd])
			free (temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	if (!temp[fd])
		temp[fd] = (char *)ft_calloc(1, sizeof(char));
	if (!temp[fd])
		return (NULL);
	temp[fd] = ft_read_and_check(fd, temp[fd]);
	line = ft_excerpt_line(temp[fd]);
	if (!line)
	{
		free(temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	temp[fd] = keep_rest(temp[fd]);
	return (line);
}

char	*ft_read_and_check(int fd, char *temp)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (new_line_check(temp) == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(temp, buffer);
	}
	if (bytes_read == -1)
	{
		free(temp);
		return (NULL);
	}
	free(buffer);
	return (temp);
}

/*
int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char *str1;
	char *str2;
	char *str3;

	//fd = open("/dev/null", O_RDONLY);
	fd1 = open("text.txt", O_RDONLY);
	str1 = get_next_line(fd1);
	printf("%s", str1);
	free(str1);
	fd2 = open("abc.txt", O_RDONLY);
	str2 = get_next_line(fd2);
	printf("%s", str2);
	free(str2);
	fd3 = open("123.txt", O_RDONLY);
	str3 = get_next_line(fd3);
	printf("%s", str3);
	free(str3);
	while (str1 && str2)
	{
		str1 = get_next_line(fd1);
		printf("%s", str1);
		free(str1);
		str2 = get_next_line(fd2);
		printf("%s", str2);
		free(str2);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/
