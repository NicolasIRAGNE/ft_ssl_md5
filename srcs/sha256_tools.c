/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:21:36 by niragne           #+#    #+#             */
/*   Updated: 2019/09/09 17:21:53 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

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

void	update_sha256_after_loop(t_sha256 *sha)
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
