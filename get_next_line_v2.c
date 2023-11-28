/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:24:07 by aghergho          #+#    #+#             */
/*   Updated: 2023/11/28 19:44:25 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static g_next   *g_line; 

static g_next	*ft_lstnew(char *str)
{
	g_next	*new;

	new = malloc (sizeof(g_next));
	if (!new)
		return(NULL);
	new->content = str;
	new->next = NULL;
	return (new);
}

static void	ft_del_head()
{
	g_next	*head;

	if (g_line)
	{
		head = g_line->next;
		free(g_line->content);
		free(g_line);
		g_line = head;		
	}
}

static void	ft_lstclear()
{
	g_next	*lst;
	
	if (!g_line)
		return ;
	lst = g_line;
	while(g_line->next)
	{
		lst = g_line->next;
		free(g_line->content);
		free(g_line->next);
		g_line =  lst;
	}
	g_line = NULL;
}

static void	ft_lstadd_back(g_next *new)
{
	g_next	*temp;
	
	if (!g_line)
	{
		g_line = new;
		return;	
	}
	temp = g_line;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	ft_strchr(char *str, char c)
{
	int	i;
	
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c);
		return (i);
	return (0);
}

int ft_check_nline(char *str)
{
	int	i;
	
	if (!str)
		return (0);
	if (str[0] == '\n')
		return(1);
	while (str[i])
	{
		if (str[i] == (char)10)
			return (i);
		printf("--%d->\t",i);
		i++;
	}
	return(i);
}



static char	*ft_strjoin(char *s1, char *s2, int len)
{
	char	*tmp;
	int		j;
	int 	i;
	char	*str;
	j = -1;
	i = 0;
	tmp = malloc(sizeof(char) * (len + ft_strchr(s1, '\0') + 1));
	printf("---%d---s1:%s,s2%s",len + ft_strchr(s1, '\0') + 1,s1,s2);
	if (!tmp)
		return (NULL);
	str = tmp;
	while (s1 && s1[i])
	{
		tmp[i] =  s1[i];
		printf("\n---%c--\n",tmp[i]);
		i++;
	}
	while (s2 && s2[++j] && j < len)
	{
		tmp[i + j] =  s2[j];
		printf("\n---%c--\n",tmp[i + j]);
	}
	if (s2 && s2[j] && s2[j] == '\n')
		tmp[i + j++] = '\n';
	tmp[i + j] = '\0';
	return (str);
}

static int	ft_edit_lst(char *str)
{
	char	*s;
	g_next	*new;
	int		r_str;
	
	s = NULL;
	if (g_line)
		s = g_line->content;
	printf("\n---------%d----------\n",ft_check_nline(str));
	s = ft_strjoin(s, str, ft_check_nline(str));
	printf("\n----joined string:%s-----\n",s);
	if (!s)
		return (0);
	new = ft_lstnew(s);
	if (!new)
		return (0);
	ft_lstadd_back(new);
	r_str = ft_strchr(str, '\n');
	if (r_str + 1 == ft_strchr(str,'\0'))
	{
		new = ft_lstnew(str + r_str + 1);
		if(!new)
			return(0);
		ft_lstadd_back(new);
	}
	return (1);
}

 char	*get_next_line(int fd)
{
	int		b_read;
	char	str[BUFFER_SIZE + 1];

	if (fd < 0 || fd > 512 || !BUFFER_SIZE)
		return (NULL);
	if (g_line)
		ft_del_head();
	b_read = read(fd, str, BUFFER_SIZE);
	if (b_read < 0)
		return (NULL);
	while (b_read > 0)
	{
		str[BUFFER_SIZE] = '\0';
		printf("\n----buffer:%s----\n",str);
		if (ft_edit_lst(str) && ft_strchr(g_line->content,'\n'))
			return(g_line->content);
		b_read = read(fd, str, BUFFER_SIZE);
	}
	if (g_line)
		return (g_line->content);
	return (NULL);
}

int main(void)
{
	int fd;
	char *line;

	fd = open("test", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return 1;
	}
	line = get_next_line(fd);
	printf("\n=======s:==========%s=======len : %ld====\n",line,strlen(line));
 		line = get_next_line(fd);
	printf("\n=======s:==========%s=======len : %ld====\n",line,strlen(line));
    free(line);
    close(fd);
    return 0;
}

