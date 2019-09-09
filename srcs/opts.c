/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:34:30 by niragne           #+#    #+#             */
/*   Updated: 2019/09/09 16:53:09 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	flag_s(t_arg_parser *parser, void *flags)
{
	t_ssl_wrapper	*wrapper;
	t_arg_parsed	*test;

	wrapper = (t_ssl_wrapper*)flags;
	if (parser->current_ptr->next)
	{
		test = (t_arg_parsed*)(parser->current_ptr->next->content);
		parser->current_ptr = parser->current_ptr->next;
		test->type = E_VALUE;
		wrapper->flags->flag_s = 1;
		wrapper->flags->flag_isfile = 0;
		wrapper->f(test->long_name, wrapper);
	}
	else
		ft_dprintf(2, "option -s requires an argument\n");
}

void	flag_p(t_arg_parser *parser, void *flags)
{
	t_ssl_wrapper *wrapper;

	(void)parser;
	wrapper = (t_ssl_wrapper*)flags;
	wrapper->flags->flag_p = 1;
	process_stdin(wrapper);
}

void	flag_r(t_arg_parser *parser, void *flags)
{
	t_ssl_wrapper *wrapper;

	(void)parser;
	wrapper = (t_ssl_wrapper*)flags;
	wrapper->flags->flag_r = 1;
}

void	flag_q(t_arg_parser *parser, void *flags)
{
	t_ssl_wrapper *wrapper;

	(void)parser;
	wrapper = (t_ssl_wrapper*)flags;
	wrapper->flags->flag_q = 1;
}

void	flag_v(t_arg_parser *parser, void *flags)
{
	t_ssl_wrapper *wrapper;

	(void)parser;
	wrapper = (t_ssl_wrapper*)flags;
	wrapper->flags->flag_v = 1;
}
