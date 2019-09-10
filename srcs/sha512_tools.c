/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:08:41 by niragne           #+#    #+#             */
/*   Updated: 2019/09/10 12:03:03 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	init_sha512(t_sha512 *sha)
{
	sha->h0 = 0x6a09e667f3bcc908;
	sha->h1 = 0xbb67ae8584caa73b;
	sha->h2 = 0x3c6ef372fe94f82b;
	sha->h3 = 0xa54ff53a5f1d36f1;
	sha->h4 = 0x510e527fade682d1;
	sha->h5 = 0x9b05688c2b3e6c1f;
	sha->h6 = 0x1f83d9abfb41bd6b;
	sha->h7 = 0x5be0cd19137e2179;
	sha->i = 16;
}

void	init_sha384(t_sha384 *sha)
{
	sha->h0 = 0xcbbb9d5dc1059ed8;
	sha->h1 = 0x629a292a367cd507;
	sha->h2 = 0x9159015a3070dd17;
	sha->h3 = 0x152fecd8f70e5939;
	sha->h4 = 0x67332667ffc00b31;
	sha->h5 = 0x8eb44a8768581511;
	sha->h6 = 0xdb0c2e0d64f98fa7;
	sha->h7 = 0x47b5481dbefa4fa4;
	sha->i = 16;
}

void	update_sha512(t_sha512 *sha)
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

void	update_sha512_after_loop(t_sha512 *sha)
{
	sha->i = 16;
	sha->h0 = sha->h0 + sha->a;
	sha->h1 = sha->h1 + sha->b;
	sha->h2 = sha->h2 + sha->c;
	sha->h3 = sha->h3 + sha->d;
	sha->h4 = sha->h4 + sha->e;
	sha->h5 = sha->h5 + sha->f;
	sha->h6 = sha->h6 + sha->g;
	sha->h7 = sha->h7 + sha->h;
}
