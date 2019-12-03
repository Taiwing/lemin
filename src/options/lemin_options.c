/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:44:58 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/03 07:30:53 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_options.h"

t_opt		g_options[OPT_COUNT + 1] = {
	{"help", 0, NULL, 'h'},
	{"ants", 1, NULL, 'a'},
	{"solution", 0, NULL, 's'},
	{"explained", 0, NULL, 'e'},
	{NULL, 0, NULL, 0},
};

static void	set_opt(int c, t_lemindata *lda, t_optdata *oda)
{
	if (c == 'h')
		lda->options |= O_HELP;
	else if (c == 'a')
	{
		lda->options |= O_ANTS;
		lda->antn = ft_atoi(oda->optarg);
	}
	else if (c == 's')
		lda->options |= O_SOLUTION;
	else if (c == 'e')
		lda->options |= O_EXPLAINED;
	else if (c == '?')
		ft_exit(NULL, 1);
}

void		get_lemin_options(t_lemindata *lda, int argc, char **argv)
{
	int			c;
	t_optdata	oda;

	init_getopt(&oda, OPTSTRING, g_options, 0);
	while ((c = ft_getopt_long(argc, argv, &oda)) != -1)
		set_opt(c, lda, &oda);
}
