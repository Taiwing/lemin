/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:59:14 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 17:57:21 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BFS_H
# define BFS_H
# include "t_lemindata.h"

typedef struct	s_bfsdata
{
	size_t		size;
	t_list		*first;
	t_list		*last;
	int			*parent;
	int			cur;
	int			dead_end;
	t_leminpath	*cur_path;
	int			adj;
}				t_bfsdata;

t_leminpath		*bfs(t_lemindata *lda);

#endif
