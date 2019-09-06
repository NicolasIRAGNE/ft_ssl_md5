/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niragne <niragne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:26:57 by niragne           #+#    #+#             */
/*   Updated: 2019/09/06 16:08:37 by niragne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

t_arg_option g_opts[] =
{
		{"string", 's', flag_s, "Print a checksum of the given string."},
		{NULL, 'p', flag_p, "Echo stdin to stdout and append the checksum to stdout."},
		{"reverse", 'r', flag_r, "Reverses the format of the output.  This helps with visual diffs.  Does nothing when combined with the -ptx options."},
		{"quiet", 'q', flag_q, "Quiet mode - only the checksum is printed out.  Overrides the -r option"},
		{"verbose", 'v', flag_v, "Verbose mode. Prints debug information."}
};

t_ssl_command g_commands[] =
{
		{"md5", process_md5, "md5 algorithm"},
		{"sha256", process_sha256, "sha256 algorithm"}
};

void	process_command(t_arg_parser *parser, char *s, t_ssl_wrapper *wrapper)
{
	size_t i;

	if (!s)
		print_usage(parser);
	i = 0;
	while (i < (sizeof(g_commands) / sizeof(*g_commands)))
	{
		if (!(ft_strcmp(g_commands[i].name, s)))
		{
			wrapper->f = g_commands[i].f;
			return ;
		}
		i++;
	}
	print_usage(parser);
}

void	process_args(t_ssl_wrapper *wrapper, t_arg_parser *parser)
{
	t_list			*lst;
	t_arg_parsed	*test;
	char			*buf;

	lst = parser->parsed->next;
	while (lst)
	{
		test = (t_arg_parsed*)lst->content;
		parser->current = test;
		parser->current_ptr = lst;
		if (test->type == E_ARG)
		{
			if ((buf = file_to_buffer(NULL, test->long_name)))
			{
				wrapper->flags->flag_s = 0;
				wrapper->file_name = test->long_name;
				wrapper->f(buf, wrapper);
				free(buf);
			}
		}
		lst = lst->next;
	}
}

void	process_stdin(t_ssl_wrapper *wrapper)
{
	char *buf;

	wrapper->flags->flag_q = 1;
	if ((buf = stdin_to_buffer(NULL))) // TODO : ici ca marche pas
	{
		wrapper->flags->flag_s = 0;
		wrapper->file_name = NULL;
		wrapper->f(buf, wrapper);
		free(buf);
	}
}

int main(int ac, char **av)
{
	t_arg_parser parser;
	t_ssl_wrapper wrapper;
	t_ssl_flags flags;
	(void)ac;
	opt_init_parser(&parser, flag_invalid, av[0]);
	opt_add_to_parser(&parser, g_opts, sizeof(g_opts));
	opt_parse_args(&parser, av + 1);
	ft_bzero(&wrapper, sizeof(wrapper));
	wrapper.flags = &flags;
	process_command(&parser, av[1], &wrapper);
	process_opt(&parser, &wrapper);
	process_args(&wrapper, &parser);
	if (parser.nb_args == 1)
		process_stdin(&wrapper);
	return (0);
}
