/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_md5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:00:44 by niragne           #+#    #+#             */
/*   Updated: 2019/09/01 14:20:35 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

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

void	get_padded_message(char *s, t_ssl_wrapper *wrapper)
{
	uint8_t *new;
	size_t formatted_len;
	size_t original_len;
	t_md5 *m = wrapper->u.md;

	original_len = ft_strlen(s);
	m->original_length = original_len;
	formatted_len = align(original_len + sizeof(uint64_t), 64);
	m->formatted_length = formatted_len;
	if (!(new = malloc(formatted_len)))
		exit(EXIT_FAILURE);	
	ft_memcpy(new, s, original_len);
	new[original_len] = 1 << 7;
	ft_bzero(new + original_len + 1, formatted_len - original_len - 1);
	set_memory_length(new + formatted_len - 8, original_len, 8, 1);
	// ft_printf("Size of message after padding: %u bits.\n", formatted_len * 8);
	//print_buff(new, formatted_len);
	m->message = new;
}

size_t	align(size_t x, size_t n)
{
	if (x == 0)
		return (n);
	else
		return ((x + n - 1) & ~(n - 1));
}

void	process_md5(char *s, t_ssl_wrapper *wrapper)
{
	t_md5 m;
	wrapper->u.md = &m;

	get_padded_message(s, wrapper);

	uint32_t h0 = 0x67452301;
	uint32_t h1 = 0xEFCDAB89;
	uint32_t h2 = 0x98BADCFE;
	uint32_t h3 = 0x10325476;

	uint32_t	*tmp;


	size_t i;
	i = 0;
	uint32_t f;
	uint32_t g;
	uint32_t a = h0;
	uint32_t b = h1;
	uint32_t c = h2;
	uint32_t d = h3;

	size_t j = 0;
	while (j < m.formatted_length / 64)
	{
		tmp = (uint32_t*)(m.message + (j * 64));
		//ft_printf("Block number %d:\n", j);
		//print_buff((uint8_t*)tmp, 64);
		a = h0;
		b = h1;
		c = h2;
		d = h3;
		while (i < 64)
		{
			if (i <= 15)
			{
				f = (b & c) | ((~b) & d);
				g = i;
			}
			else if (i >= 16 && i <= 31)
			{
				f = (d & b) | ((~d) & c);
				g = ((5 * i + 1) % 16);
			}
			else if (i >= 32 && i <= 47)
			{
				f = b ^ c ^ d;
				g = ((3 * i + 5) % 16);
			}
			else if (i >= 48 && i <= 63)
			{
				f = c ^ (b | ~d);
				g = (7 * i) % 16;
			}
			uint32_t swp;
			swp = d;
			d = c;
			c = b;
			b = b + LEFTROTATE((a + f + g_sines[i] + tmp[g]), g_shifts[i]);
			a = swp;
			i++;
		}
		j += 1;
		i = 0;
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
	}
	if (!wrapper->flags->flag_q)
	{
		if (wrapper->flags->flag_s)
			ft_printf("MD5 (\"%s\") = ", s);
		else
			ft_printf("MD5 (%s) = ", wrapper->file_name);
	}
	ft_printf("%08x%08x%08x%08x\n", swap_uint32(h0), swap_uint32(h1), swap_uint32(h2), swap_uint32(h3));
}
