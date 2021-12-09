/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyoshiha <iyoshiha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:46:32 by iyoshiha          #+#    #+#             */
/*   Updated: 2021/12/10 07:16:42 by iyoshiha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_newline(char *save, t_txt *txt)
{
	txt->save_len = 0;
	txt->newline_index = GNL_NEWLINE_NOT_FOUND;
	if (save == NULL)
		return (GNL_NEWLINE_NOT_FOUND);
	while (save[txt->save_len] != '\0')
	{
		if ((save[txt->save_len] == '\n') \
		&& (txt->newline_index == GNL_NEWLINE_NOT_FOUND))
			txt->newline_index = txt->save_len;
		txt->save_len++;
	}
	return (txt->newline_index);
}

void	*manage_buf(t_buf_cmd command, char **save, char **buf, t_txt *txt)
{
	char	*for_free;

	if (command == malloc_buf)
	{
		*buf = malloc(BUFFER_SIZE + END_STR);
		if (*buf == NULL)
			return (MEMORY_ERROR);
	}
	else if (command == save_buf)
	{
		(*buf)[txt->len_read] = '\0';
		if (save[txt->fd] == FIRST_TIME)
		{
			save[txt->fd] = ft_strjoin(NULL, *buf);
			return (save[txt->fd]);
		}
		for_free = save[txt->fd];
		save[txt->fd] = ft_strjoin(for_free, *buf);
		free(for_free);
		return (save[txt->fd]);
	}
	else if (command == free_buf)
		if (*buf != NULL)
			free(*buf);
	return (MEMORY_SUCCESS);
}

void	*create_oneline(t_txt *txt, char **save)
{
	int		i;
	char	*old_save;

	i = 0;
	txt->line = (char *)malloc(txt->save_len + END_STR);
	if (txt->line == MEMORY_ERROR)
		return (MEMORY_ERROR);
	while (save[txt->fd][i] != '\0')
	{
		txt->line[i] = save[txt->fd][i];
		i = NEXT i;
		if (save[txt->fd][i OF_PREVIOUS] == '\n')
			break ;
	}
	txt->line[i] = '\0';
	if (GNL_LAST_LINE == ((txt->len_read == END_OF_FILE) && \
	(txt->newline_index == GNL_NEWLINE_NOT_FOUND)))
		return (save_free(save, txt, in_create_newline));
	old_save = save[txt->fd];
	save[txt->fd] = ft_strjoin(NULL, (old_save + NEXT txt->newline_index));
	free(old_save);
	return (save[txt->fd]);
}

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*buf;
	t_txt		txt;

	txt.fd = fd;
	if (manage_buf(malloc_buf, save, &buf, &txt) == MEMORY_ERROR)
		return (MEMORY_ERROR);
	find_newline(save[fd], &txt);
	while (UNTIL_REACH_EOF_OR_FIND_NEWLINE)
	{
		if (ERROR_OR_FINISH == read_and_detect_err_fin(save, buf, &txt))
			return (ERROR_OR_FINISH);
		if (END_OF_FILE == txt.len_read)
			break ;
		if (MEMORY_ERROR == manage_buf(save_buf, save, &buf, &txt))
			return (MEMORY_ERROR);
		if (GNL_NEWLINE_NOT_FOUND != find_newline(save[fd], &txt))
			break ;
	}
	manage_buf(free_buf, save, &buf, &txt);
	if ((txt.len_read == END_OF_FILE) && save[fd][0] == '\0')
		return (save_free(save, &txt, in_gnl));
	if (create_oneline(&txt, save) == MEMORY_ERROR)
		return (MEMORY_ERROR);
	return (txt.line);
}
