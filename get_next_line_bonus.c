/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+      */
/*   By: lbetella <lbetella@student.42malaga.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/12 11:03:30 by lbetella         #+#    #+#              */
/*   Updated: 2026/10/13 12:21:23 by lbetella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *string)
{
	char		*temp;
	ssize_t		readed;

	if (ft_strchr(string, '\n'))
		return (string);
	readed = 1;
	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (free(string), NULL);
	while (readed != 0)
	{
		readed = read(fd, temp, BUFFER_SIZE);
		if (readed == -1)
			return (free(string), free(temp), NULL);
		temp[readed] = '\0';
		string = ft_strjoin(string, temp);
		if (!string)
			return (free(temp), NULL);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	free(temp);
	return (string);
}

char	*ft_extract(char *string)
{
	char	*temp;
	int		i;

	i = 0;
	if (!string[0])
		return (NULL);
	while (string[i] != '\n' && string[i] != '\0')
		i++;
	if (string[i] == '\n')
		i++;
	temp = malloc((i + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (string[i] != '\n' && string[i] != '\0')
	{
		temp[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
		temp[i++] = '\n';
	temp[i] = '\0';
	return (temp);
}

char	*ft_clean(char *string)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	j = 0;
	while (string[i] != '\n' && string[i] != '\0')
		i++;
	if (string[i] == '\0' || string[i + 1] == '\0')
		return (free(string), NULL);
	i++;
	rest = malloc((ft_strlen(string) - i + 1) * sizeof(char));
	if (!rest)
		return (free(string), NULL);
	while (string[i + j] != '\0')
	{
		rest[j] = string[i + j];
		j++;
	}
	rest[j] = '\0';
	free(string);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*string[1024];
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	string[fd] = ft_read(fd, string[fd]);
	if (!string[fd])
		return (NULL);
	result = ft_extract(string[fd]);
	if (!result)
	{
		free(string[fd]);
		string[fd] = NULL;
		return (NULL);
	}
	string[fd] = ft_clean(string[fd]);
	return (result);
}
