/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:24:07 by aghergho          #+#    #+#             */
/*   Updated: 2023/11/26 19:43:51 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static g_next   *g_line; 


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
	g_line	*lst;
	
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

static int	ft_lstadd_back(g_next new)
{
	g_next	*temp;
	int		endline;
	
	endline = ft_strchr(new->content,'\n');	
	if (new && ! endline && (ft_strchr(new->content,'\0') - endline - 1))
	{
		temp = g_line;
		while (temp->next)
			temp = temp->next;
		temp->next=new;
		return (1);
	}
	else
		if (!ft_edit_lst(new->content))
			return (0);
	return (1);
}

static char	*ft_nltrim(char *str)
{
	char	*s;
	int		i;
	int		t_len;
	
	i = 0;
	t_len = ft_strchr(str,'\n');
	s = malloc(sizeof(char) * t_len);
	if (!s)
		return (NULL);
	while (i < t_len)
		s[i] = str[i++];
	s[i] = '\0';
	free(str);
	return (s);  
}

static int	ft_edit_lst(char *str)
{
	
}
ft_strjoin();
ft_strchr();

char *get_next_line(int fd)
{

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
	printf("\n=======s:==========%s=======len : %ld====\n",line,ft_strlen(line));
    free(line);
    close(fd);
    return 0;
}

