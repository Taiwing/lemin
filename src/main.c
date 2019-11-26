/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:36:48 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/26 12:47:31 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_options.h"
#include "print_help.h"
#include "lemin_parser.h"

int	main(int argc, char **argv)
{
	t_lemindata	lda;

	ft_bzero(&lda, sizeof(t_lemindata));	//init data structure
	/*if (argc != 2)
	{
		ft_printf("ERROR > no map file OR file doesnt exist\n");
		return (1);
	}*/
	get_lemin_options(&lda, argc, argv);	//handle arguments
	if (lda.options & O_HELP)
		print_help(argv[0]);
	else
	{
		if (!lemin_parser(&lda))	//read input
			ft_printf("DO SOLVER\n");//if input is valid: execute lemin
	}
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (lda.ret);
}
