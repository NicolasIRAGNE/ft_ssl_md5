/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:33:42 by niragne           #+#    #+#             */
/*   Updated: 2019/09/10 11:29:07 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

uint32_t	swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

uint64_t	swap_uint64(uint64_t val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL)
		| ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL)
		| ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | (val >> 32);
}

void		swap_uint32_array(uint32_t *array, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		array[i] = swap_uint32(array[i]);
		i++;
	}
}

void		swap_uint64_array(uint64_t *array, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		array[i] = swap_uint64(array[i]);
		i++;
	}
}
