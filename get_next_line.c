/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:28:57 by ddos              #+#    #+#             */
/*   Updated: 2023/12/02 10:05:17 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static  g_next  *g_line;

int     ft_strlen(char  *str)
{
    int     i;
    
    if (!str)
        return (0);
    i = 0;
    while (str[i])
        i++;
    return (i);
}

int     check_end_line(char *str)
{
    int     i;
    
    if (!str)
        return (-1);
    i = 0;
	if (str[0] == '\n')
		return (0);
    while (str[i])
    {
        if (str[i] == '\n')
    	{
			// printf("\n-ch_end_line res:-%d--\n",i);
			return (i);
		}
        i++;
    }
	// printf("\n-ch_end_line res:-0--\n");
    return (-1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int		i;
	int		len;

	len = ft_strlen(src);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;
	
	j = 0;
	i = ft_strlen(dest);
	while (src && src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*sub_str(char	*str ,int len)
{
	int		i;
	char	*s;
	
	i = 0;
	s = malloc (sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	while (str[i] && i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char    *str_join(char *s1, char *s2)
{
    char    *str;
    int     j;
	int		i;
    
    i = ft_strlen(s1);
    j = ft_strlen(s2);
	// printf("\n===s1:%s==s2%s\n",s1,s2);
	str = malloc (sizeof(char) * (i + j + 1));
    if (!str)
        return (NULL);
    ft_strcpy(str, s1);
	ft_strcat(str, s2);
    return (str);
}

int ft_edit_node(char *str)
{
	int		p_endl;
	
	printf("\n===str==%s==\n",str);
	if (check_end_line(g_line->current) >= 0 && g_line->n_line)
		g_line->current = g_line->n_line;
	p_endl = check_end_line(str);
	g_line->current = sub_str(str , p_endl);
	if (!g_line->current)
		return(0);
	printf("\n===g_line->current==%s==\n",g_line->current);
	if (g_line->n_line)
		free(g_line->n_line);
	g_line->n_line =  sub_str(str + p_endl + 1 , ft_strlen(str + p_endl + 1));
	if (!g_line->n_line)
		return (0);
	return (1);
}

char	*get_line(int fd)
{
	char	*buf;
	int		b_read;
	
	printf("SEGV");
	if (g_line->n_line)
		g_line->current = g_line->n_line;
	buf = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	b_read = read(fd, buf, BUFFER_SIZE);
	while(check_end_line(g_line->current) < 0 && b_read >0)
	{
		buf[b_read] = '\0';
		printf("\n==buf==:%s\n",buf);
		g_line->current = str_join(g_line->current, buf);
		if (check_end_line(g_line->current) >= 0 || b_read < BUFFER_SIZE)
			break;
		printf("\n=====g_line->current:%s======\n",g_line->current);
		b_read = read(fd, buf,BUFFER_SIZE);
	}
	printf("\n=====g_line->current:%s======\n",g_line->current);
	printf("\n=====g_line->nline:%s======\n",g_line->n_line);
	free(buf);
	return(g_line->current);
}

int 	gen_node()
{
    g_next *new_node = malloc(sizeof(g_next));
	
    if (!new_node) 
        return 0;
    g_line = new_node;
    g_line->current = NULL;
    g_line->n_line = NULL;
    return 1;
}

char *get_next_line(int fd)
{
	char	*line;
	
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!g_line)
		if (!gen_node())
			return (NULL);
	printf("SEGV");
	line = get_line(fd);
	printf("\n===line==%s==\n",line);
	if (check_end_line(line) + 1 != ft_strlen(line))
	{
		printf("editing node");
		if (ft_edit_node(line))
			line = g_line->current;
		else
		{
			free(g_line->current);
			free(g_line->n_line);
			return (NULL);
		}
	}
	return (line);
}

int main()
{
    int fd = open("test2", O_RDONLY);
    char *line;

    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }
	int	i;

	i = 0;
	line = get_next_line(fd);
	{
		if (line == NULL)
		{
			printf("\n============== yeah line is NULL\n");
			// break;
		}
		else
		{
			// printf("\n============== yeah line is !NULL\n");
		}
		// printf("\n==========new line number in the line  :%d==================\n",get_nline(line));
		printf("\n=================line %d==============\nstr:%s======================",++i,line);
	}
	printf("\n===g_line->nline:%s===\n",g_line->n_line);
	
		line = get_next_line(fd);
	{
		if (line == NULL)
		{
			printf("\n============== yeah line is NULL\n");
			// break;
		}
		else
		{
			// printf("\n============== yeah line is !NULL\n");
		}
		// printf("\n==========new line number in the line  :%d==================\n",get_nline(line));
		printf("\n=================line %d==============\nstr:%s======================",++i,line);
	}
	printf("\n===g_line->nline:%s===\n",g_line->n_line);
			line = get_next_line(fd);
	{
		if (line == NULL)
		{
			printf("\n============== yeah line is NULL\n");
			// break;
		}
		else
		{
			// printf("\n============== yeah line is !NULL\n");
		}
		// printf("\n==========new line number in the line  :%d==================\n",get_nline(line));
		printf("\n=================line %d==============\nstr:%s======================",++i,line);
	}
	printf("\n===g_line->nline:%s===\n",g_line->n_line);
    // Perform operations with the read line
    close(fd);

    return 0; // Exit the program successfully
}










// char *get_next_line(int fd)
// int     update_node(char *str)
// {
// 	char	*s;
// 	int		flag;
	
// 	printf("\n=====================-----str:%s---===================================\n",str);
// 	printf("\n---g_nline:%s---\n",g_line->n_line);
// 	printf("\n===================g_line->current:%s======================\n",g_line->current);
// 		// printf("\ng_line->n_line:%s\n",g_line->n_line);
// 	// if (g_line->n_line)
// 	// 	g_line->current = g_line->n_line;
// 	printf("\n---g_Current:%s---\n",g_line->current);
// 	if (check_end_line(g_line->n_line) && str);
// 		if (!str_join(g_line->n_line, str));
// 	if ( check_end_line(g_line->current) >= 0 && check_end_line(g_line->n_line) >= 0)
// 	{
// 		s = str_join(g_line->n_line, (char *)0);
		
// 	}
// 	else if (check_end_line(g_line->current) >= 0 && check_end_line(g_line->n_line) <= 0)
// 		s = str_join(NULL, g_line->n_line);
// 	// printf("\n===================\n======================================g_line->current:%s==========\n======================\n",g_line->current);
// 	if (!s)
// 		return (0);
// 	printf("\njoined str:%s\n",s);
// 	if (g_line->current)
// 		free(g_line->current);
// 	g_line->current = s;
// 	printf("\n===================g_line->current:%s======================\n",g_line->current);
// 	flag = check_end_line(str);
// 	if (flag >= 0)
// 	{
// 		// printf("\nyuh we need a new line flag:%d\n",flag);
// 		printf("\n========start of substring:%s=============len: %d=\n",str + flag + 1, ft_strlen(str + flag + 1));
// 		g_line->n_line = sub_str(str + flag + 1, ft_strlen(str + flag + 1));
// 		if (!g_line->n_line)
// 			return (0);
// 	}
// 	printf("===============done======\n");
// 	return (1);	
// }
// {
// 	char	*buf;
// 	int		b_read;
// 	int		i;
	
	
// 	if (fd < 0 || fd > 512 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	if (!g_line)
// 		if (!ft_gen_node())
// 			return (NULL);
// 	buf = malloc (sizeof(char) * BUFFER_SIZE + 1);
// 	if (!buf)
// 		return (NULL);
// 	b_read = read(fd, buf, BUFFER_SIZE);
// 	while (b_read > 0)
// 	{
// 		buf[b_read] = '\0';
// 		printf("\n===nbuffer : %s=====\n",buf);
// 		if (! update_node(buf))
// 			return (NULL);
// 		if (check_end_line(g_line->current) >= 0 || b_read < BUFFER_SIZE)
// 			return (g_line->current);
// 		b_read = read(fd, buf, BUFFER_SIZE);
// 	}
// 	if (g_line->n_line && check_end_line(g_line->current) >= 0 && ft_strlen(g_line->n_line) && update_node((char *)NULL))
// 	{
// 		printf("ddd");
// 		free(buf);	
// 		return (g_line->current);
// 	}
// 	return (NULL);
// }