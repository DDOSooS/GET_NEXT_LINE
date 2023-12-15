/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GET_NEXT_LINE.C                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:09:43 by ddos              #+#    #+#             */
/*   Updated: 2023/12/05 21:22:02 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*g_line;

char	*edit_line(char *str, int len)
{
	char	*s;

	s = NULL;
	s = str_sub(str, len + 1);
	if (!s)
		return (NULL);
	g_line = str_sub(str + len + 1, ft_strlen(str + len + 1));
	if (! g_line)
	{
		free(s);
		free(g_line);
		return (NULL);
	}
	free (str);
	return (s);
}

char	*str_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	j = -1;
	i = 0;
	if (s1)
		i += ft_strlen(s1);
	i += ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (! str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*get_lin(int fd)
{
	char	*buffer;
	int		b_read;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	b_read = read(fd, buffer, BUFFER_SIZE);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		g_line = str_join(g_line, buffer);
		if (!g_line || check_end_line(g_line) >= 0
			|| b_read < BUFFER_SIZE)
			break ;
		b_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (!g_line || b_read == -1)
	{
		free(g_line);
		g_line = NULL;
	}
	return (g_line);
}

char	*format_last_line(char *str)
{
	char	*s;
	int		i;

	s = (char *)malloc (ft_strlen(str) + 1);
	if (!s)
	{
		free(g_line);
		g_line = NULL;
		return (NULL);
	}
	i = 0;
	while (str && str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	free(g_line);
	g_line = NULL;
	return (s);
}

char	*get_next_line(int fd)
{
	char	*str;
	int		e_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (! g_line)
		g_line = NULL;
	str = get_lin(fd);
	if (!str)
		return (NULL);
	e_line = check_end_line(str);
	if (e_line >= 0 && e_line + 1 != ft_strlen(str))
	{
		str = edit_line(str, e_line);
		if (! str)
			return (NULL);
	}
	else if (e_line < 0 || ft_strlen(str) == e_line + 1)
		str = format_last_line(str);
	return (str);
}

// #include <string.h>

// int main()
// {
// 	int	fd = open("test4.txt",O_RDONLY);
// 	char	*line;

// 	int	i;

// 	i = 0;
// (line = get_next_line(fd)) ;
// 	{
// 		printf("====================%s", line);
// 		free(line);
// 		i++;
// 	}
// 	return (0);
// }
