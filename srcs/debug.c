/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:18:22 by niragne           #+#    #+#             */
/*   Updated: 2019/09/09 17:20:40 by niragne          ###   ########.fr       */
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

void	print_padded_message(uint8_t *msg, size_t len)
{
	ft_printf("Size of message after padding: %u bits.\n",
		len * 8);
	print_buff(msg, len);
	ft_printf("\n");
}

void	print_schedule(uint32_t *array)
{
	size_t i;

	ft_printf("Schedule:\n");
	i = 0;
	while (i < 64)
	{
		if (!(i % 8) && i)
			ft_printf("\n");
		ft_printf("s[%2d] = %-12u ", i, array[i]);
		i++;
	}
	ft_printf("\n\n");
}
