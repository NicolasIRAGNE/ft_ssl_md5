/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:38:53 by niragne           #+#    #+#             */
/*   Updated: 2019/09/09 16:41:14 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	ssl_perror(char *s, t_arg_parser *parser)
{
	ft_dprintf(2, "%s: ", parser->prog_name);
	perror(s);
}
