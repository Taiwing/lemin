/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:43:05 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/19 14:43:08 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_options.h"

void	help(char *name)
{
	ft_printf("usage: %s [-h] | [-se[a number_of_ants]] [< map]\n\n", name);
	ft_printf("\t-h | --help: print this\n");
	ft_printf("\t-s | --solution: only print the solution\n");
	ft_printf("\t-e | --explained: explain the algorithm\n");
	ft_printf("\t-a | --ants: next argument is the number of ants\n");
}
