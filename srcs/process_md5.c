/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_md5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:00:44 by niragne           #+#    #+#             */
/*   Updated: 2019/09/09 15:29:18 by niragne          ###   ########.fr       */
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

static void	get_padded_message(char *s, t_ssl_wrapper *wrapper)
{
	uint8_t *new;
	size_t formatted_len;
	size_t original_len;
	t_md5 *m = wrapper->u.md;

	if (!wrapper->flags->flag_isfile)
		original_len = ft_strlen(s);
	else
		original_len = wrapper->file_length;
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

void	init_md5(t_md5 *md)
{
	md->h0 = 0x67452301;
	md->h1 = 0xEFCDAB89;
	md->h2 = 0x98BADCFE;
	md->h3 = 0x10325476;
	md->a = md->h0;
	md->b = md->h1;
	md->c = md->h2;
	md->d = md->h3;
	md->i = 0;
}

void	process_md5(char *s, t_ssl_wrapper *wrapper)
{
	t_md5 m;
	wrapper->u.md = &m;

	init_md5(&m);
	get_padded_message(s, wrapper);
	size_t j = 0;
	while (j < m.formatted_length / 64)
	{
		m.ptr = (uint32_t*)(m.message + (j * 64));
		// ft_printf("Block number %d:\n", j);
		// print_buff((uint8_t*)m.ptr, 64);
		// ft_printf("\n");
		m.a = m.h0;
		m.b = m.h1;
		m.c = m.h2;
		m.d = m.h3;
		md5_16(&m);
		md5_32(&m);
		md5_48(&m);
		md5_64(&m);
		j += 1;
		m.i = 0;
		m.h0 += m.a;
		m.h1 += m.b;
		m.h2 += m.c;
		m.h3 += m.d;
	}
	md5_print_result(s, wrapper);
}

void	md5_print_result(char *s, t_ssl_wrapper *wrapper)
{
	t_md5 *md;
	md = wrapper->u.md;
	if (!wrapper->flags->flag_q && !wrapper->flags->flag_r)
	{
		if (wrapper->flags->flag_s)
			ft_printf("MD5 (\"%s\") = ", s);
		else
			ft_printf("MD5 (%s) = ", wrapper->file_name);
	}
	ft_printf("%08x%08x%08x%08x", swap_uint32(md->h0),
		swap_uint32(md->h1), swap_uint32(md->h2), swap_uint32(md->h3));
	if (wrapper->flags->flag_r && !wrapper->flags->flag_q)
	{
		if (wrapper->flags->flag_s)
			ft_printf(" \"%s\"", s);
		else
			ft_printf(" %s", wrapper->file_name);
	}
	ft_printf("\n");
	free(md->message);
}
