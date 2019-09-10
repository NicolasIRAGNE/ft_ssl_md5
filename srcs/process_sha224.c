/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_sha224.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 13:17:46 by niragne           #+#    #+#             */
/*   Updated: 2019/09/10 10:47:49 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static uint32_t g_k[] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void		get_padded_message(char *s, t_ssl_wrapper *wrapper)
{
	uint8_t		*new;
	size_t		formatted_len;
	size_t		original_len;
	t_sha224	*m;

	m = wrapper->u.sha224;
	if (!wrapper->flags->flag_isfile && s)
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
	set_memory_length(new + formatted_len - 8, original_len, 8, 0);
	if (wrapper->flags->flag_v)
		print_padded_message(new, formatted_len);
	m->message = new;
}

void			sha224_schedule(t_ssl_wrapper *wrapper, size_t j)
{
	t_sha224	*sha;
	uint32_t	s0;
	uint32_t	s1;

	sha = wrapper->u.sha224;
	sha->ptr = (uint32_t*)(sha->message + (j * 64));
	swap_uint32_array(sha->ptr, 16);
	ft_memcpy(sha->array, sha->ptr, 16 * sizeof(uint32_t));
	while (sha->i < 64)
	{
		s0 = rightrotate(sha->array[sha->i - 15], 7) ^ rightrotate(
			sha->array[sha->i - 15], 18) ^ (sha->array[sha->i - 15] >> 3);
		s1 = rightrotate(sha->array[sha->i - 2], 17) ^ rightrotate(
			sha->array[sha->i - 2], 19) ^ (sha->array[sha->i - 2] >> 10);
		sha->array[sha->i] = sha->array[sha->i - 16] + s0
			+ sha->array[sha->i - 7] + s1;
		sha->i++;
	}
	if (wrapper->flags->flag_v)
		print_schedule(sha->array);
}

void			sha224_loop(t_ssl_wrapper *wrapper)
{
	t_sha224	*sha;

	sha = wrapper->u.sha224;
	while (sha->i < 64)
	{
		sha->s1 = rightrotate(sha->e, 6) ^ rightrotate(sha->e, 11)
			^ rightrotate(sha->e, 25);
		sha->ch = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
		sha->tmp1 = sha->h + sha->s1 + sha->ch + g_k[sha->i]
			+ sha->array[sha->i];
		sha->s0 = rightrotate(sha->a, 2) ^ rightrotate(sha->a, 13)
			^ rightrotate(sha->a, 22);
		sha->maj = (sha->a & sha->b) ^ (sha->a & sha->c) ^ (sha->b & sha->c);
		sha->tmp2 = sha->s0 + sha->maj;
		sha->h = sha->g;
		sha->g = sha->f;
		sha->f = sha->e;
		sha->e = sha->d + sha->tmp1;
		sha->d = sha->c;
		sha->c = sha->b;
		sha->b = sha->a;
		sha->a = sha->tmp1 + sha->tmp2;
		sha->i++;
	}
}

void			process_sha224(char *s, t_ssl_wrapper *wrapper)
{
	t_sha224	sha;
	size_t		j;

	j = 0;
	wrapper->u.sha224 = &sha;
	init_sha224(&sha);
	get_padded_message(s, wrapper);
	while (j < sha.formatted_length / 64)
	{
		sha224_schedule(wrapper, j);
		update_sha256((t_sha256*)&sha);
		sha224_loop(wrapper);
		update_sha256_after_loop((t_sha256*)&sha);
		j += 1;
	}
	sha224_print_result(s, wrapper);
}

void			sha224_print_result(char *s, t_ssl_wrapper *wrapper)
{
	t_sha224 *sha;

	sha = wrapper->u.sha224;
	if (wrapper->flags->flag_p && s)
		ft_printf("%s", s);
	if (!wrapper->flags->flag_q && !wrapper->flags->flag_r)
	{
		if (wrapper->flags->flag_s)
			ft_printf("SHA224 (\"%s\") = ", s);
		else
			ft_printf("SHA224 (%s) = ", wrapper->file_name);
	}
	ft_printf("%08x%08x%08x%08x%08x%08x%08x", sha->h0, sha->h1, sha->h2,
		sha->h3, sha->h4, sha->h5, sha->h6);
	if (wrapper->flags->flag_r && !wrapper->flags->flag_q)
	{
		if (wrapper->flags->flag_s)
			ft_printf(" \"%s\"", s);
		else
			ft_printf(" %s", wrapper->file_name);
	}
	ft_printf("\n");
	free(sha->message);
}
