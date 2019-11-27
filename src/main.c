/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:36:48 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/27 18:49:18 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_options.h"
#include "lemin_parser.h"
#include "lemin_solver.h"
#include "print_lemin.h"

int	main(int argc, char **argv)
{
	t_lemindata	lda;
	int			turns;
	t_list		*solution;

	turns = -1;
	solution = NULL;
	ft_bzero(&lda, sizeof(t_lemindata));
	get_lemin_options(&lda, argc, argv);
	if (lda.options & O_HELP)
		help(argv[0]);
	else
	{
		if (!lemin_parser(&lda))
			solution = lemin_solver(&lda, &turns);
		print_lemin(&lda, solution, turns);
	}
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (lda.ret);
}
