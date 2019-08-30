/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:34:30 by niragne           #+#    #+#             */
/*   Updated: 2019/08/30 13:16:22 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	flag_s(t_arg_parser *parser, void *flags)
{
	(void)parser;
	(void)flags;
	t_arg_parsed *test;

	test = (t_arg_parsed*)(parser->current_ptr->next->content);
	process_md5(test->long_name);
}

void	flag_p(t_arg_parser *parser, void *flags)
{
	(void)parser;
	(void)flags;
	ft_printf("flag p\n");
}

void	flag_r(t_arg_parser *parser, void *flags)
{
	(void)parser;
	(void)flags;
	ft_printf("flag r\n");
}

void	flag_q(t_arg_parser *parser, void *flags)
{
	(void)parser;
	(void)flags;
	ft_printf("flag q\n");
}

void	flag_invalid(t_arg_parser *parser, void *flags)
{
	(void)parser;
	(void)flags;
	ft_printf("flag invalid\n");
}
