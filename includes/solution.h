/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:09:03 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/19 09:25:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLUTION_H
# define SOLUTION_H
# include "t_lemindata.h"

void	add_path(t_lemindata *lda, t_list **solution, t_leminpath *path);
void	replace_path(t_list **solution, t_leminpath *orig, t_leminpath *new);
int		test_solution(t_list *solution, t_leminpath *to_add, int antn);

#endif
