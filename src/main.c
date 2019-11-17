/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:36:48 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/17 23:25:45 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_options.h"
#include "print_help.h"

int	main(int argc, char **argv)
{
	t_lemindata	lda;

	ft_bzero(&lda, sizeof(t_lemindata));	//init data structure
	get_lemin_options(&lda, argc, argv);	//handle arguments
	if (lda.options & O_HELP)
		print_help(argv[0]);
	else
	{
		//read input
		//if input is valid: execute lemin
		ft_printf("DO NOTHING\n");
	}
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (lda.ret);
}
