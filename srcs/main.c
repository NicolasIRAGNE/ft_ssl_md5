/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:26:57 by niragne           #+#    #+#             */
/*   Updated: 2019/08/30 12:41:58 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

t_arg_option g_opts[] =
{
		{"string", 's', flag_s, "Print a checksum of the given string."},
		{"", 'p', flag_p, "Echo stdin to stdout and append the checksum to stdout."},
		{"", 'r', flag_r, "Reverses the format of the output.  This helps with visual diffs.  Does nothing when combined with the -ptx options."},
		{"", 'q', flag_q, "Quiet mode - only the checksum is printed out.  Overrides the -r option"}
};

int main(int ac, char **av)
{
	t_arg_parser parser;
	(void)ac;
	(void)av;
	opt_init_parser(&parser, flag_invalid, av[0]);
	opt_add_to_parser(&parser, g_opts, sizeof(g_opts));
	opt_parse_args(&parser, av + 1);
	process_opt(&parser, NULL);
	return (0);
}
