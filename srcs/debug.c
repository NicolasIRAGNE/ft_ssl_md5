/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:18:22 by niragne           #+#    #+#             */
/*   Updated: 2019/08/30 16:50:03 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	print_buff(uint8_t *s, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if (!(i % 8) && i)
			ft_printf("\n");
		if (!(i % 64) && i)
			ft_printf("\n");
		ft_printf("%08b ", s[i]);
		i++;
	}
	ft_printf("\n");
}
