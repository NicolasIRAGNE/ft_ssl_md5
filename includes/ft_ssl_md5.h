/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:27:14 by niragne           #+#    #+#             */
/*   Updated: 2019/09/09 18:05:40 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "libft.h"

typedef	struct		s_ssl_flags
{
	int				flag_s : 1;
	int				flag_p : 1;
	int				flag_q : 1;
	int				flag_r : 1;
	int				flag_v : 1;
	int				flag_isfile : 1;
}					t_ssl_flags;

typedef struct		s_md5
{
	size_t			original_length;
	size_t			formatted_length;
	size_t			i;
	uint8_t			*message;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		h0;
	uint32_t		h1;
	uint32_t		h2;
	uint32_t		h3;
	uint32_t		f;
	uint32_t		g;
	uint32_t		*ptr;
}					t_md5;

typedef struct		s_sha256
{
	size_t			original_length;
	size_t			formatted_length;
	size_t			i;
	uint8_t			*message;
	uint32_t		*ptr;
	uint32_t		h0;
	uint32_t		h1;
	uint32_t		h2;
	uint32_t		h3;
	uint32_t		h4;
	uint32_t		h5;
	uint32_t		h6;
	uint32_t		h7;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
	uint32_t		s1;
	uint32_t		ch;
	uint32_t		tmp1;
	uint32_t		s0;
	uint32_t		maj;
	uint32_t		tmp2;
	uint32_t		array[64];
}					t_sha256;

typedef struct s_ssl_wrapper	t_ssl_wrapper;

typedef struct		s_ssl_command
{
	char			*name;
	void			(*f)(char *s, t_ssl_wrapper *wrapper);
	char			*usage;
}					t_ssl_command;

typedef union		u_ssl_union
{
	t_md5			*md;
	t_sha256		*sha256;
}					t_ssl_union;

struct				s_ssl_wrapper
{
	t_ssl_flags		*flags;
	char			*file_name;
	size_t			file_length;
	void			(*f)(char *s, t_ssl_wrapper *wrapper);
	t_ssl_union		u;
};

void				flag_s(t_arg_parser *parser, void *flags);
void				flag_p(t_arg_parser *parser, void *flags);
void				flag_q(t_arg_parser *parser, void *flags);
void				flag_r(t_arg_parser *parser, void *flags);
void				flag_v(t_arg_parser *parser, void *flags);
void				flag_invalid(t_arg_parser *parser, void *flags);
void				process_md5(char *s, t_ssl_wrapper *wrapper);
void				md5_16(t_md5 *m);
void				md5_32(t_md5 *m);
void				md5_48(t_md5 *m);
void				md5_64(t_md5 *m);
void				md5_full(t_md5 *m);
void				md5_print_result(char *s, t_ssl_wrapper *wrapper);
void				process_sha256(char *s, t_ssl_wrapper *wrapper);
void				sha256_print_result(char *s, t_ssl_wrapper *wrapper);
size_t				align(size_t x, size_t n);
uint64_t			swap_uint64(uint64_t val);
uint32_t			swap_uint32(uint32_t val);
void				swap_uint32_array(uint32_t *array, size_t len);
void				print_buff(uint8_t *s, size_t len);
void				set_memory_length(uint8_t *i, size_t length, int size,
						char is_little_endian);
uint32_t			leftrotate(uint32_t x, size_t c);
uint32_t			rightrotate(uint32_t x, size_t c);
char				*file_to_buffer(t_ssl_wrapper *wrapper, char *name);
char				*stdin_to_buffer(t_ssl_wrapper *wrapper);
void				process_stdin(t_ssl_wrapper *wrapper);
void				ssl_perror(char *s, t_arg_parser *parser);
void				print_padded_message(uint8_t *msg, size_t len);
void				print_schedule(uint32_t *array);
void				init_sha256(t_sha256 *sha);
void				update_sha256(t_sha256 *sha);
void				update_sha256_after_loop(t_sha256 *sha);

#endif
