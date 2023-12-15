/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:15:41 by aghergho          #+#    #+#             */
/*   Updated: 2023/12/15 11:13:56 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>

char	*get_next_line(int fd);
int		ft_strlen(char *str);
int		check_end_line(char *str);
char	*str_sub(char *str, int len);

#endif
