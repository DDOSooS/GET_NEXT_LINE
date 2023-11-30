/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:28:57 by ddos              #+#    #+#             */
/*   Updated: 2023/11/30 06:35:18 by ddos             ###   ########.fr       */
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
        return (0);
    i = 0;
	if (str[0] == '\n')
		return (1);
    while (str[i])
    {
        if (str[i] == '\n' || str[i] == EOF)
    	{
			// printf("\n-ch_end_line res:-%d--\n",i);
			return (i);
		}
        i++;
    }
	// printf("\n-ch_end_line res:-0--\n");
    return (0);
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

char	*ft_strncat(char *dest, char *src, int len)
{
	int	i;
	int	j;
	
	j = 0;
	// printf("\n======ft_strncat========\ndest:%s,src:%s,len:%d\n",dest,src,len);
	i = ft_strlen(dest);
	// printf("\ndest len:%d\n",i);
	while (j < len)
	{
		dest[i + j] = src[j];
		// printf("\ndest[%d]:%c\n",i,dest[i]);
		j++;
	}
	// printf("\n src[%d] :%c ='n' ? %d \n",j,src[j],src[j] == '\n');
	if (src[j]== '\n')
	{
		dest[i + j] = '\n';
		// printf("end of line");
		j++;
	}
	dest[i + j] = '\0';
	// printf("\nstr:%s",dest);
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
	// printf("\nlen:%d\n",len);
	while (str[i] && i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	// printf("\nsub_str:%s\n",str);
	return (s);
}

char    *str_join(char *s1, char *s2)
{
    char    *str;
    int     i;
    int     j;
    
	printf("\n---------------str_join-------------------\n--s1:%s,s2:%s======\n",s1,s2);
    i = ft_strlen(s1);
    j = check_end_line(s2);
	// printf("\ncheck end of lien | file %d\n",j);
    if (!j)
        j = ft_strlen(s2);
    str = malloc (sizeof(char) * (i + j + 1));
	printf("\n---t_len------------------------endofs2:%d----:%d\n",i + j + 1,check_end_line(s2));
    if (!str)
        return (NULL);
    ft_strcpy(str, s1);
    ft_strncat(str, s2, j);
	printf("\n-------------joined_str----------------\nstr:%s\n",str);
	printf("\nt_len of str:%d\n",ft_strlen(str));
    return (str);
}



int     update_node(char *str)
{
	char	*s;
	int		flag;
	
	// printf("\n-----str:%s\n",str);
	// printf("\n---g_nline:%s---\n",g_line->n_line);
		// printf("\ng_line->current:%s\n",g_line->current);
		// printf("\ng_line->n_line:%s\n",g_line->n_line);
	// if (g_line->n_line)
	// 	g_line->current = g_line->n_line;
	// printf("\n---g_Current:%s---\n",g_line->current);
	if (check_end_line(g_line->n_line) )
		g_line->current = NULL;
	else
		g_line->current = g_line->n_line;	
	s = str_join(g_line->current, str);
	if (!s)
		return (0);
	// printf("\njoined str:%s\n",s);
	if (g_line->current)
		free(g_line->current);
	g_line->current = s;
	flag = check_end_line(str);
	if (flag)
	{
		// printf("\nyuh we need a new line\n");
		g_line->n_line = sub_str(str + flag + 1, ft_strlen(str) - flag);
		if (!g_line->n_line)
			return (0);
	}
	return (1);	
}


int ft_gen_node()
{
    g_next *new_node = malloc(sizeof(g_next));
    if (!new_node) {
        return 0;
    }

    g_line = new_node; // Assign the allocated memory address to g_line
    g_line->current = NULL;
    g_line->n_line = NULL;

    return 1;
}


char *get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		b_read;
	
	if (fd < 0 || fd > 512 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!g_line)
		if (!ft_gen_node())
			return (NULL);
	while (read(fd, buf, BUFFER_SIZE) > 0)
	{
		buf[BUFFER_SIZE] = '\0';
		printf("\n==================================================\nbufer:%s======\n",buf);
		if (! update_node(buf))
			return (NULL);
		if (check_end_line(g_line->current))
			return (g_line->current);
	}
	// printf("\n------------g_n__line:%s\n",g_line->n_line);
	// printf("\n------------g__line:%s\n",g_line->n_line);
	if (g_line->n_line && check_end_line(g_line->current) && update_node(g_line->n_line))
	{
		// printf("\ng_line->current:%s\n",g_line->current);
		// printf("\ng_line->n_line:%s\n",g_line->n_line);
		return (g_line->current);
	}
	return (NULL);
}

int main() {
    int fd = open("test2", O_RDONLY); // Use O_RDONLY for read-only access
    char *line;

    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }
	int	i;

	i = 0;
	while(line = get_next_line(fd))
	{
		if (line == NULL)
			break;
		printf("\nline %d:%s",++i,line);
	}
    // Perform operations with the read line

    // Close the file
    close(fd);

    return 0; // Exit the program successfully
}