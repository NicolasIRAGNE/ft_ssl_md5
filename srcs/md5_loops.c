/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_loops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 13:46:29 by niragne           #+#    #+#             */
/*   Updated: 2019/09/02 14:05:39 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	md5_16(t_md5 *m)
{
	uint32_t swp;

	while (m->i <= 15)
	{
		m->f = (m->b & m->c) | ((~m->b) & m->d);
		m->g = m->i;
		swp = m->d;
		m->d = m->c;
		m->c = m->b;
		m->b = m->b + LEFTROTATE((m->a + m->f + g_sines[m->i] + m->ptr[m->g]), g_shifts[m->i]);
		m->a = swp;
		m->i++;
	}
}

void	md5_32(t_md5 *m)
{
	uint32_t swp;

	while (m->i >= 16 && m->i <= 31)
	{
		m->f = (m->d & m->b) | ((~m->d) & m->c);
		m->g = ((5 * m->i + 1) % 16);
		swp = m->d;
		m->d = m->c;
		m->c = m->b;
		m->b = m->b + LEFTROTATE((m->a + m->f + g_sines[m->i] + m->ptr[m->g]), g_shifts[m->i]);
		m->a = swp;
		m->i++;
	}
}

void	md5_48(t_md5 *m)
{
	uint32_t swp;

	while (m->i >= 32 && m->i <= 47)
	{
		m->f = m->b ^ m->c ^ m->d;
		m->g = ((3 * m->i + 5) % 16);
		swp = m->d;
		m->d = m->c;
		m->c = m->b;
		m->b = m->b + LEFTROTATE((m->a + m->f + g_sines[m->i] + m->ptr[m->g]), g_shifts[m->i]);
		m->a = swp;
		m->i++;
	}
}

void	md5_64(t_md5 *m)
{
	uint32_t swp;

	while (m->i >= 48 && m->i <= 63)
	{
		m->f = m->c ^ (m->b | ~m->d);
		m->g = (7 * m->i) % 16;
		swp = m->d;
		m->d = m->c;
		m->c = m->b;
		m->b = m->b + LEFTROTATE((m->a + m->f + g_sines[m->i] + m->ptr[m->g]), g_shifts[m->i]);
		m->a = swp;
		m->i++;
	}
}
