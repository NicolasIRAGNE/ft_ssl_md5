/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:59:11 by niragne           #+#    #+#             */
/*   Updated: 2019/09/10 11:35:25 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

uint32_t	leftrotate(uint32_t x, size_t c)
{
	return ((((x) << (c)) | ((x) >> (32 - (c)))));
}

uint32_t	rightrotate(uint32_t x, size_t c)
{
	return ((((x) >> (c)) | ((x) << (32 - (c)))));
}

uint64_t	leftrotate64(uint64_t x, size_t c)
{
	return ((((x) << (c)) | ((x) >> (64 - (c)))));
}

uint64_t	rightrotate64(uint64_t x, size_t c)
{
	return ((((x) >> (c)) | ((x) << (64 - (c)))));
}
