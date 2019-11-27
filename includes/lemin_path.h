/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_path.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:27:43 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 19:08:58 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_PATH_H
# define LEMIN_PATH_H
# include "t_lemindata.h"

void		set_path(t_leminpath *path, t_lemindata *lda,
				int edge[2], t_leminpath *path_id);
void		del_path_node(void *content, size_t content_size);
void		destroy_path(t_lemindata *lda, t_leminpath **path);
int			path_len_cmp(t_leminpath *p1, t_leminpath *p2);
t_leminpath	*build_path(t_lemindata *lda, int *parent);

#endif
