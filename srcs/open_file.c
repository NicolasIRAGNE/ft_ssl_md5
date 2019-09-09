/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:30:01 by niragne           #+#    #+#             */
/*   Updated: 2019/09/09 15:27:19 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

char	*update_buffer(char *dest, char *src, size_t current_size, size_t size)
{
	char *tmp;

	if (dest == NULL)
	{
		dest = malloc(size + 1);
		if (!dest)
			return (NULL);
		ft_memcpy(dest, src, size);
		return (dest);
	}
	tmp = dest;
	dest = malloc(current_size + size + 1);
	ft_memcpy(dest, tmp, current_size);
	ft_memcpy(dest + current_size, src, size);
	free(tmp);
	return (dest);
}

char	*file_to_buffer(t_ssl_wrapper *wrapper, char *name)
{
	char	*ret;
	char	buffer[BUFF_SIZE + 1];
	size_t	total_size;
	int		rd;
	int		fd;

	ret = NULL;
	total_size = 0;
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror(name);
		return (NULL);
	}
	while ((rd = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		ret = update_buffer(ret, buffer, total_size, rd);
		total_size += rd;
	}
	close(fd);
	if (rd < 0)
	{
		perror(name);
		return (NULL);
	}
	ret[total_size] = 0;
	wrapper->file_length = total_size;
	return (ret);
}

char	*stdin_to_buffer(t_ssl_wrapper *wrapper)
{
	char	*ret;
	char	buffer[BUFF_SIZE + 1];
	size_t	total_size;
	int		rd;

	(void)wrapper;
	ret = NULL;
	total_size = 0;
	while ((rd = read(STDIN_FILENO, buffer, BUFF_SIZE)) > 0)
	{
		ret = update_buffer(ret, buffer, total_size, rd);
		total_size += rd;
	}
	if (rd < 0)
	{
		perror("test");
		return (NULL);
	}
	ret[total_size] = 0;
	return (ret);
}
