/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:55:12 by niragne           #+#    #+#             */
/*   Updated: 2019/09/09 16:55:56 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	set_memory_length(uint8_t *init_mem, size_t length, int size,
											char is_little_endian)
{
	int		i;
	char	byte;
	size_t	value;
	uint8_t	*mem;
	int		shift;

	i = 0;
	value = length * 8;
	mem = init_mem;
	while (i < size)
	{
		shift = 8 * i;
		if (!is_little_endian)
			shift = 8 * (size - 1 - i);
		byte = (char)(value >> shift);
		ft_memset(mem, byte, 1);
		mem++;
		i++;
	}
}

size_t	align(size_t x, size_t n)
{
	if (x == 0)
		return (n);
	else
		return ((x + n - 1) & ~(n - 1));
}
