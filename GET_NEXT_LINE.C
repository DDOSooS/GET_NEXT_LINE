/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GET_NEXT_LINE.C                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:09:43 by ddos              #+#    #+#             */
/*   Updated: 2023/12/02 18:29:32 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *line[FD_MAX];

int	ft_strlen(char *str)
{
	int     i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

//checking the end_of_line
int	check_end_line(char *str)
{
	int     i;

	i = 0;
	if (!str)
		return (-1);
	if (str[0] == '\n' || str[i] == EOF)
		return (0);
	while(str[i])
	{
		if (str[i] == '\n')
			return(i);
		i++;
	}
	return (-1);
}

//substring the str
char	*str_sub(char *str, int len)
{    
	char    *s;
	int     i;

	s = (char *) malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*edit_line(char *str, int len, int fd)
{
	char	*s;

	s = NULL;
	s = str_sub(str, len);
	if (!s)
		return (NULL);
	line[fd] = str_sub(str + len + 1, ft_strlen(str + len + 1));
	if (! line[fd])
	{
		free(s);
		free(str);
		return (NULL);
	}
	free (str);
	return (s);   
}

char	*str_join(char *s1, char *s2)
{
	int     i;
	int     j;
	char    *str;

	i = 0;
	j = -1;
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
	return (str);
}

char    *get_line(int fd)
{
	char    *buffer;
	int     b_read;

	buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	b_read = read(fd, buffer, BUFFER_SIZE);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		line[fd] = str_join(line[fd], buffer);
		if (!line[fd] || check_end_line(line[fd]) >= 0 || b_read < BUFFER_SIZE)
			break;
		b_read = read(fd, buffer, BUFFER_SIZE);        
    }
	free(buffer);
	if (!line[fd])
		return (NULL);
	return (line[fd]);
}

char    *format_last_line(char *str,int fd)
{
    char    *s;
    int     i;

    s = (char *)malloc (ft_strlen(str) + 1);
    if (!s)
        return (NULL);
    i = 0;
    while (str && str[i])
    {
        s[i] = str[i];
        i++;
    }
	s[i] = '\0';
	free(line[fd]);
	line[fd] = NULL;
	return (s);
}

char    *get_next_line(int fd)
{
    char    *str;
    int     e_line;
    
    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
        return (NULL);
    str = get_line(fd);
    if (!str)
        return (NULL);
    e_line = check_end_line(str);
	if (e_line >= 0 && e_line + 1 != ft_strlen(str))
    {
        str = edit_line(str, e_line, fd);
        if (! str)
            return (NULL);
    }
    else if (e_line < 0 || (e_line == 0 && ft_strlen(str) == e_line + 1))
        str = format_last_line(str,fd);	
    return (str);
}

int main()
{
    int fd = open("test2", O_RDONLY);
    char *line;
	int	i;

    if (fd == -1)
    {
        perror("Error opening the file");
        return 1;
    }
	i = 0;
    while((line = get_next_line(fd))!= NULL)
		printf("\n=================line %d==============\nstr:%s==",++i,line);
    close(fd);
    return 0; // Exit the program successfully
}