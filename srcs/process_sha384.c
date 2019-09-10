/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_sha384.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 13:17:46 by niragne           #+#    #+#             */
/*   Updated: 2019/09/10 13:49:20 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static uint64_t g_k[] =
{
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538,
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f,
	0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4,
	0x76f988da831153b5, 0x983e5152ee66dfab,
	0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
	0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791,
	0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63,
	0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
	0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60,
	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c,
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84,
	0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

static void		get_padded_message(char *s, t_ssl_wrapper *wrapper)
{
	uint8_t		*new;
	size_t		formatted_len;
	size_t		original_len;
	t_sha384	*m;

	m = wrapper->u.sha384;
	if (!wrapper->flags->flag_isfile && s)
		original_len = ft_strlen(s);
	else
		original_len = wrapper->file_length;
	m->original_length = original_len;
	formatted_len = align(original_len + sizeof(uint64_t) + 9, 128);
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

void			sha384_schedule(t_ssl_wrapper *wrapper, size_t j)
{
	t_sha384	*sha;
	uint64_t	s0;
	uint64_t	s1;

	sha = wrapper->u.sha384;
	sha->ptr = (uint64_t*)(sha->message + (j * 128));
	swap_uint64_array(sha->ptr, 16);
	ft_memcpy(sha->array, sha->ptr, 16 * sizeof(uint64_t));
	while (sha->i < 80)
	{
		s0 = rightrotate64(sha->array[sha->i - 15], 1) ^ rightrotate64(
			sha->array[sha->i - 15], 8) ^ (sha->array[sha->i - 15] >> 7);
		s1 = rightrotate64(sha->array[sha->i - 2], 19) ^ rightrotate64(
			sha->array[sha->i - 2], 61) ^ (sha->array[sha->i - 2] >> 6);
		sha->array[sha->i] = sha->array[sha->i - 16] + s0
			+ sha->array[sha->i - 7] + s1;
		sha->i++;
	}
	if (wrapper->flags->flag_v)
		print_schedule_64(sha->array);
}

void			sha384_loop(t_ssl_wrapper *wrapper)
{
	t_sha384	*sha;

	sha = wrapper->u.sha384;
	while (sha->i < 80)
	{
		sha->s1 = rightrotate64(sha->e, 14) ^ rightrotate64(sha->e, 18)
			^ rightrotate64(sha->e, 41);
		sha->ch = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
		sha->tmp1 = sha->h + sha->s1 + sha->ch + g_k[sha->i]
			+ sha->array[sha->i];
		sha->s0 = rightrotate64(sha->a, 28) ^ rightrotate64(sha->a, 34)
			^ rightrotate64(sha->a, 39);
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

void			process_sha384(char *s, t_ssl_wrapper *wrapper)
{
	t_sha384	sha;
	size_t		j;

	j = 0;
	wrapper->u.sha384 = &sha;
	init_sha384(&sha);
	get_padded_message(s, wrapper);
	while (j < sha.formatted_length / 128)
	{
		sha384_schedule(wrapper, j);
		update_sha512((t_sha512*)&sha);
		sha384_loop(wrapper);
		update_sha512_after_loop((t_sha512*)&sha);
		j += 1;
	}
	sha384_print_result(s, wrapper);
}

void			sha384_print_result(char *s, t_ssl_wrapper *wrapper)
{
	t_sha384 *sha;

	sha = wrapper->u.sha384;
	if (wrapper->flags->flag_p && s)
		ft_printf("%s", s);
	if (!wrapper->flags->flag_q && !wrapper->flags->flag_r)
	{
		if (wrapper->flags->flag_s)
			ft_printf("SHA384 (\"%s\") = ", s);
		else
			ft_printf("SHA384 (%s) = ", wrapper->file_name);
	}
	ft_printf("%016lx%016lx%016lx%016lx%016lx%016lx", sha->h0,
		sha->h1, sha->h2, sha->h3, sha->h4, sha->h5);
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
