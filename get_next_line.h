/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:15:41 by aghergho          #+#    #+#             */
/*   Updated: 2023/11/30 04:00:04 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#define BUFFER_SIZE  42

# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

char *get_next_line(int fd);
typedef struct	get_next_line
{
	char					*current;
	char					*n_line;
}	g_next;

#endif
