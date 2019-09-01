/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:34:30 by niragne           #+#    #+#             */
/*   Updated: 2019/09/01 14:24:18 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	flag_s(t_arg_parser *parser, void *flags)
{
	(void)parser;
	t_ssl_wrapper *wrapper;
	t_arg_parsed *test;

	wrapper = (t_ssl_wrapper*)flags;
	if (parser->current_ptr->next)
	{
		test = (t_arg_parsed*)(parser->current_ptr->next->content);
		parser->current_ptr = parser->current_ptr->next;
		test->type = E_VALUE;
		wrapper->flags->flag_s = 1;
		wrapper->f(test->long_name, wrapper);
	}
	else
	{
		ft_dprintf(2, "option -s requires an argument\n");
	}
}

void	flag_p(t_arg_parser *parser, void *flags)
{
	(void)parser;
	(void)flags;
	t_ssl_wrapper *wrapper;

	wrapper = (t_ssl_wrapper*)flags;
	wrapper->flags->flag_p = 1;
	ft_printf("flag p\n");
}

void	flag_r(t_arg_parser *parser, void *flags)
{
	(void)parser;
	(void)flags;
	t_ssl_wrapper *wrapper;

	wrapper = (t_ssl_wrapper*)flags;
	wrapper->flags->flag_r = 1;
	ft_printf("flag r\n");
}

void	flag_q(t_arg_parser *parser, void *flags)
{
	(void)parser;
	(void)flags;
	t_ssl_wrapper *wrapper;

	wrapper = (t_ssl_wrapper*)flags;
	wrapper->flags->flag_q = 1;
}

void	flag_invalid(t_arg_parser *parser, void *flags)
{
	(void)parser;
	(void)flags;

	ft_printf("flag invalid\n");
}
