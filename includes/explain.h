/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explain.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:13:50 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/19 14:37:14 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPLAIN_H
# define EXPLAIN_H
# include "t_lemindata.h"

void	explain_split(t_lemindata *lda, t_leminpath *path,
				t_leminpath *overlap_path, t_leminpath *split[2]);
void	explain_path(t_lemindata *lda, t_leminpath *path);
void	explain_solution(t_lemindata *lda, int turns, int new_turns);

#endif
