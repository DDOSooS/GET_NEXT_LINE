/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:30:38 by aghergho          #+#    #+#             */
/*   Updated: 2023/12/11 16:30:49 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# define FD_MAX 1024

char	*get_next_line(int fd);
int		ft_strlen(char *str);
int		check_end_line(char *str);
char	*str_sub(char *str, int len);

#endif
