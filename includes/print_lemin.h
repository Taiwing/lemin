/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lemin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:20:41 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/19 16:24:34 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_LEMIN_H
# define PRINT_LEMIN_H
# include "t_lemindata.h"

enum				e_state {INACTIVE, MOVING, ARRIVED};

typedef struct		s_ant
{
	enum e_state	state;
	t_list			*room;
}					t_ant;

void				print_lemin(t_lemindata *lda, t_list *solution, int turns);

#endif
