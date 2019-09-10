/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:52:14 by niragne           #+#    #+#             */
/*   Updated: 2019/09/10 12:17:33 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	flag_invalid(t_arg_parser *parser, void *flags)
{
	(void)parser;
	(void)flags;
	if (parser->current->type == E_OPT_SHORT)
	{
		ft_printf("%s: illegal option -- %c\n", parser->prog_name,
			parser->current->short_name);
		print_usage(parser);
	}
	else if (parser->current->type == E_OPT_LONG)
	{
		ft_printf("%s: illegal option -- %s\n", parser->prog_name,
			parser->current->long_name);
		print_usage(parser);
	}
}
