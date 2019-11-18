/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:27:22 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 19:14:37 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lemindata.h"

void		set_path(t_leminpath *path, t_lemindata *lda,
				int edge[2], t_leminpath *path_id)
{
	int		u;
	int		v;
	t_list	*ptr;

	ptr = path->nodes;
	v = *(int *)ptr->content;
	while (ptr->next)
	{
		u = v;
		v = *(int *)ptr->next->content;
		lda->e[u][v] = edge[FORWARD];
		lda->e[v][u] = edge[BACKWARD];
		lda->v[u]->path = path_id;
		ptr = ptr->next;
	}
}

void		del_path_node(void *content, size_t content_size)
{
	(void)content_size;
	ft_memdel((void **)&content);
}

void		destroy_path(t_lemindata *lda, t_leminpath **path)
{
	set_path(*path, lda, (int[2]){0, 0}, NULL);
	ft_lstdel(&(*path)->nodes, del_path_node);
	ft_memdel((void **)path);
}

int			path_len_cmp(t_leminpath *p1, t_leminpath *p2)
{
	return (p1->len - p2->len);
}

t_leminpath	*build_path(t_lemindata *lda, int *parent)
{
	t_leminpath	*path;
	int			cur;

	path = ft_memalloc(sizeof(t_leminpath));
	ft_lst_push_front(&path->nodes, &lda->t, sizeof(int));
	cur = lda->t;
	while (cur != lda->s)
	{
		cur = parent[cur] - 1;
		path->overlap = !path->overlap ? lda->v[cur]->path : path->overlap;
		ft_lst_push_front(&path->nodes, &cur, sizeof(int));
		++path->len;
	}
	return (path);
}
