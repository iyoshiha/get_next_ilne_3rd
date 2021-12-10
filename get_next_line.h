/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyoshiha <iyoshiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:46:07 by iyoshiha          #+#    #+#             */
/*   Updated: 2021/12/10 13:25:27 by iyoshiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define END_OF_FILE 0
# define READ_ERR -1
# define FIRST_TIME ((void *)0)
# define FINISH ((void *)0)
# define ERROR_OR_FINISH ((void *)0)
# define MEMORY_SUCCESS ((void *)0x7fffff)
# define MEMORY_ERROR ((void *)0)
# define END_STR 1
# define NEXT 1+
# define OF_PREVIOUS -1
# define CONVERT_TO_LEN 1+
# define GNL_NEWLINE_NOT_FOUND -1
# define GNL_LAST_LINE 1
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

typedef struct s_txt
{
	size_t	save_len;
	ssize_t	newline_index;
	ssize_t	len_read;
	int		fd;
	char	*line;
}				t_txt;

typedef enum e_buf_cmd
{
	save_buf,
	malloc_buf,
	free_buf
}			t_buf_cmd;

typedef enum e_place_save
{
	in_create_newline,
	in_gnl
}			t_place_save;

char	*ft_strjoin(char const *s1, char const *s2);
ssize_t	find_newline(char *save, t_txt *txt);
void	*manage_buf(t_buf_cmd command, char **save, char **buf, t_txt *txt);
void	*save_free(char **save, t_txt *txt, t_place_save place);
void	*create_oneline(t_txt *txt, char **save);
char	*get_next_line(int	fd);
void	*read_and_detect_err_fin(char **save, char *buf, t_txt *txt);
size_t	ft_strlen(const char *s);

#endif
