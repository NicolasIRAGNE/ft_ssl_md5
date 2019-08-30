/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:27:14 by niragne           #+#    #+#             */
/*   Updated: 2019/08/30 16:18:48 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD65
# define FT_SSL_MD65

#include "libft.h"

void	flag_s(t_arg_parser *parser, void *flags);
void	flag_p(t_arg_parser *parser, void *flags);
void	flag_q(t_arg_parser *parser, void *flags);
void	flag_r(t_arg_parser *parser, void *flags);
void	flag_invalid(t_arg_parser *parser, void *flags);

void	process_md5(char *s);
size_t	align(size_t x, size_t n);
uint64_t swap_uint64(uint64_t val);
uint32_t swap_uint32(uint32_t val);
void	print_buff(uint8_t *s, size_t len);

extern uint32_t g_sines[];
extern uint32_t g_shifts[];

#endif
