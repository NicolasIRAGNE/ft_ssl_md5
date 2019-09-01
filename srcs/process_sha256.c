/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_sha256.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 13:17:46 by niragne           #+#    #+#             */
/*   Updated: 2019/09/01 14:18:42 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	process_sha256(char *s, t_ssl_wrapper *wrapper)
{
	if (wrapper->flags->flag_s)
		ft_printf("SHA256 (\"%s\") = ", s);
	else
		ft_printf("SHA256 (%s) = ", wrapper->file_name);
	ft_printf("Not implemented yet. Sorry !\n");
}
