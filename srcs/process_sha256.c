/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_sha256.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 13:17:46 by niragne           #+#    #+#             */
/*   Updated: 2019/09/02 17:01:03 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static const uint32_t k[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


static void	get_padded_message(char *s, t_ssl_wrapper *wrapper)
{
	uint8_t *new;
	size_t formatted_len;
	size_t original_len;
	t_sha256 *m = wrapper->u.sha256;

	original_len = ft_strlen(s);
	m->original_length = original_len;
	formatted_len = align(original_len + sizeof(uint64_t), 64);
	m->formatted_length = formatted_len;
	if (!(new = malloc(formatted_len)))
		exit(EXIT_FAILURE);	
	ft_memcpy(new, s, original_len);
	new[original_len] = 1 << 7;
	ft_bzero(new + original_len + 1, formatted_len - original_len - 1);
	set_memory_length(new + formatted_len - 8, original_len, 8, 0);
	// ft_printf("Size of message after padding: %u bits.\n", formatted_len * 8);
	//print_buff(new, formatted_len);
	m->message = new;
}

void	init_sha256(t_sha256 *sha)
{
	sha->h0 = 0x6a09e667;
	sha->h1 = 0xbb67ae85;
	sha->h2 = 0x3c6ef372;
	sha->h3 = 0xa54ff53a;
	sha->h4 = 0x510e527f;
	sha->h5 = 0x9b05688c;
	sha->h6 = 0x1f83d9ab;
	sha->h7 = 0x5be0cd19;
	sha->i = 16;
}

void	update_sha256(t_sha256 *sha)
{
	sha->a = sha->h0;
	sha->b = sha->h1;
	sha->c = sha->h2;
	sha->d = sha->h3;
	sha->e = sha->h4;
	sha->f = sha->h5;
	sha->g = sha->h6;
	sha->h = sha->h7;
	sha->i = 0;
}

void	print_schedule(uint32_t *array)
{
	size_t i = 0;

	while (i < 64)
	{
		if (!(i % 8) && i)
			ft_printf("\n");
		ft_printf("s[%2d]=%-12u ", i, array[i]);
		i++;
	}
	ft_printf("\n");
}

void	process_sha256(char *s, t_ssl_wrapper *wrapper)
{
	t_sha256 sha;

	wrapper->u.sha256 = &sha;
	init_sha256(&sha);
	get_padded_message(s, wrapper);
	print_buff(sha.message, 64);
	size_t j = 0;

	uint32_t s0;
	uint32_t s1;
	while (j < sha.formatted_length / 64)
	{
		sha.ptr = (uint32_t*)(sha.message + (j * 64));
		ft_memcpy(sha.array, sha.ptr, 16 * sizeof(uint32_t));
		while (sha.i < 64)
		{
			s0 = RIGHTROTATE(sha.array[sha.i - 15], 7) ^ RIGHTROTATE(sha.array[sha.i - 15], 18) ^ (sha.array[sha.i - 15] >> 3);
			s1 = RIGHTROTATE(sha.array[sha.i - 2], 17) ^ RIGHTROTATE(sha.array[sha.i - 2], 19) ^ (sha.array[sha.i - 2] >> 10);
			sha.array[sha.i] = sha.array[sha.i - 16] + s0 + sha.array[sha.i - 7] + s1;
			sha.i++;
		}
		print_schedule(sha.array);
		update_sha256(&sha);
		while (sha.i < 64)
		{
			uint32_t S1 = RIGHTROTATE(sha.e, 6) ^ RIGHTROTATE(sha.e, 11) ^ RIGHTROTATE(sha.e, 25);
			uint32_t ch = (sha.e & sha.f) ^ ((~sha.e) & sha.g);
			uint32_t tmp1 = sha.h + S1 + ch + k[sha.i] + sha.array[sha.i];
			uint32_t S0 = RIGHTROTATE(sha.a, 2) ^ RIGHTROTATE(sha.a, 13) ^ RIGHTROTATE(sha.a, 22);
			uint32_t maj = (sha.a & sha.b) ^ (sha.a & sha.c) ^ (sha.b & sha.c);
			uint32_t tmp2 = S0 + maj;
			sha.h = sha.g;
			sha.g = sha.f;
			sha.f = sha.e;
			sha.e = sha.d + tmp1;
			sha.d = sha.c;
			sha.c = sha.b;
			sha.b = sha.a;
			sha.a = tmp1 + tmp2;
			ft_printf("[%2d] A=%12u B=%12u C=%12u D=%12u E=%12u F=%12u G=%12u H=%12u\n", sha.i, sha.a, sha.b,sha.c,sha.d,sha.e,sha.f,sha.g,sha.h);
			sha.i++;
		}
		j += 1;
		sha.i = 16;
		sha.h0 = sha.h0 + sha.a;
		sha.h1 = sha.h1 + sha.b;
		sha.h2 = sha.h2 + sha.c;
		sha.h3 = sha.h3 + sha.d;
		sha.h4 = sha.h4 + sha.e;
		sha.h5 = sha.h5 + sha.f;
		sha.h6 = sha.h6 + sha.g;
		sha.h7 = sha.h7 + sha.h;
	}
	if (wrapper->flags->flag_s)
		ft_printf("SHA256 (\"%s\") = ", s);
	else
		ft_printf("SHA256 (%s) = ", wrapper->file_name);
	ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x\n", sha.h0,sha.h1,sha.h2,sha.h3,sha.h4,sha.h5,sha.h6,sha.h7);
}
