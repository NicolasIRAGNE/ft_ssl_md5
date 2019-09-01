/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:27:14 by niragne           #+#    #+#             */
/*   Updated: 2019/09/01 15:38:15 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD65
# define FT_SSL_MD65

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include "libft.h"

typedef	struct	s_ssl_flags
{
	int	flag_s : 1;
	int	flag_p : 1;
	int	flag_q : 1;
	int	flag_r : 1;
}				t_ssl_flags;

typedef struct	s_md5
{
	size_t	original_length;
	size_t	formatted_length;
	uint8_t	*message;
}				t_md5;

typedef struct s_ssl_wrapper t_ssl_wrapper;

typedef struct	s_ssl_command
{
	char	*name;
	void	(*f)(char *s, t_ssl_wrapper *wrapper);
	char	*usage;
}				t_ssl_command;

struct	s_ssl_wrapper
{
	t_ssl_flags	*flags;
	char		*file_name;
	void	(*f)(char *s, t_ssl_wrapper *wrapper);
	union {
		t_md5 *md;
	}	u;
};


void	flag_s(t_arg_parser *parser, void *flags);
void	flag_p(t_arg_parser *parser, void *flags);
void	flag_q(t_arg_parser *parser, void *flags);
void	flag_r(t_arg_parser *parser, void *flags);
void	flag_invalid(t_arg_parser *parser, void *flags);

void	process_md5(char *s, t_ssl_wrapper *wrapper);
void	process_sha256(char *s, t_ssl_wrapper *wrapper);
size_t	align(size_t x, size_t n);
uint64_t swap_uint64(uint64_t val);
uint32_t swap_uint32(uint32_t val);
void	print_buff(uint8_t *s, size_t len);

extern uint32_t g_sines[];
extern uint32_t g_shifts[];

#endif
