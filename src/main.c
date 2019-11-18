/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:36:48 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 09:58:12 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_options.h"
#include "print_help.h"
#include "lemin_parser.h"
#include "lemin_solver.h"

int	main(int argc, char **argv)
{
	t_lemindata	lda;
	t_list		*solution;

	ft_bzero(&lda, sizeof(t_lemindata));
	get_lemin_options(&lda, argc, argv);
	if (lda.options & O_HELP)
		print_help(argv[0]);
	else
	{
		if (!lemin_parser(&lda))
			solution = lemin_solver(&lda);
		//print_lemin(&lda, solution);
	}
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (lda.ret);
}
