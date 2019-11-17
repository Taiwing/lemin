/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:36:48 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/17 20:26:40 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lemindata.h"

int	main(int argc, char **argv)
{
	t_lemindata	lda;

	(void)argc;
	(void)argv;
	//init data structure
	ft_bzero(&lda, sizeof(t_lemindata));
	//handle arguments
//	get_lemin_options(&lda, argc, argv);
	//read input
	//if input is valid: execute lemin
	ft_printf("OK\n");
	return (0);
}
