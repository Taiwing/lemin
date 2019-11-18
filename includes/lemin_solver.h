/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_solver.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:56:14 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 11:58:37 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_SOLVER_H
# define LEMIN_SOLVER_H
# include "t_lemindata.h"

t_list	*lemin_solver(t_lemindata *lda, t_list **solution);

#endif
