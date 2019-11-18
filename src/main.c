/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:36:48 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 09:04:00 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_options.h"
#include "print_help.h"
#include "lemin_parser.h"

int	main(int argc, char **argv)
{
	t_lemindata	lda;

	ft_bzero(&lda, sizeof(t_lemindata));	//init data structure
	get_lemin_options(&lda, argc, argv);	//handle arguments
	if (lda.options & O_HELP)
		print_help(argv[0]);
	else
	{
		if (!lemin_parser(&lda))	//read input
			ft_printf("DO SOLVER\n");//if input is valid: execute lemin
		ft_printf("DO NOTHING\n");
	}
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (lda.ret);
}
