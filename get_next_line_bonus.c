/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:39:24 by dmontgen          #+#    #+#             */
/*   Updated: 2020/01/14 09:35:43 by dmontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*create_last_str(char *str, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	*line = ft_substr(str, 0, i);
	if (ft_strchr(str, '\n') != NULL)
	{
		temp = str;
		str = ft_strdup(ft_strchr(str, '\n'));
		free(temp);
	}
	else if (ft_strchr(str, '\0') != NULL)
	{
		temp = str;
		str = ft_strdup(ft_strchr(str, '\0'));
		free(temp);
		return (str);
	}
	return (str);
}

char	*check_str(char *str, char **line)
{
	char *temp;

	temp = str;
	if (str[0] == '\n' && str[1] == '\0')
	{
		str = ft_strdup(ft_strchr(str, '\n') + 1);
		free(temp);
	}
	else if (str[0] == '\n' && str[1] != '\0' &&
			ft_strchr(str + 1, '\n'))
	{
		str = ft_strdup(ft_strchr(str, '\n') + 1);
		free(temp);
		str = create_last_str(str, line);
	}
	else if (str[0] == '\n' && str[1] != '\0' &&
			ft_strchr(str + 1, '\n') == NULL)
	{
		str = ft_strdup(ft_strchr(str, '\n') + 1);
		free(temp);
	}
	return (str);
}

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!(str = (char*)malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	while (i < size + 1)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

int		ft_free(char **str)
{
	char *temp;

	temp = *str;
	free(temp);
	*str = NULL;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[255];
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	char		*temp;

	if ((!str[fd] && !(str[fd] = ft_strnew(0))) ||
			(fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0))
		return (-1);
	str[fd] = check_str(str[fd], line);
	if (ft_strchr(str[fd], '\n') == NULL)
	{
		while (!(ft_strchr(str[fd], '\n')) &&
				(ret = read(fd, buf, BUFFER_SIZE)))
		{
			buf[ret] = '\0';
			temp = str[fd];
			str[fd] = ft_strjoin(str[fd], buf);
			free(temp);
		}
		str[fd] = create_last_str(str[fd], line);
	}
	if (ft_strlen(str[fd]) == 0 && !ret)
		return (ft_free(&str[fd]));
	return (1);
}
