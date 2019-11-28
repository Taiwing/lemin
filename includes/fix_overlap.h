/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_overlap.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 09:28:16 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/28 17:23:24 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIX_OVERLAP_H
# define FIX_OVERLAP_H
# include "t_lemindata.h"

void	del_path(t_leminpath **path);
int		fix_overlap(t_lemindata *lda, t_leminpath **path, t_list **solution);

#endif
