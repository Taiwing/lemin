/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:58:05 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 19:12:03 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bfs.h"
#include "lemin_path.h"

static void	queue_append(t_bfsdata *bda, int node)
{
	if (!bda->first)
	{
		bda->first = ft_lstnew(&node, sizeof(int));
		bda->last = bda->first;
	}
	else
	{
		ft_lst_push_back(&bda->last, &node, sizeof(int));
		bda->last = bda->last->next;
	}
}

static void	init_bfsdata(t_bfsdata *bda, t_lemindata *lda)
{
	if (!bda->size)
	{
		bda->size = lda->vlen * sizeof(int);
		bda->parent = ft_memalloc(bda->size);
	}
	else
		ft_bzero((void *)bda->parent, bda->size);
	queue_append(bda, lda->s);
	lda->v[lda->s]->path = NULL;
	lda->v[lda->t]->path = NULL;
}

static int	queue_popleft(t_bfsdata *bda)
{
	int	node;

	node = *(int *)bda->first->content;
	ft_lst_discard(NULL, &bda->first);
	bda->last = bda->first ? bda->last : bda->first;
	return (node);
}

static int	is_visitable(t_lemindata *lda, t_bfsdata *bda)
{
	int	cur_parent;
	int	ret;

	ret = 0;
	cur_parent = bda->parent[bda->cur];
	if (!bda->parent[bda->adj])
	{
		if (bda->cur_path
			&& ((lda->e[cur_parent - 1][bda->cur] == -1
			&& lda->e[bda->cur][bda->adj])
			|| (lda->e[cur_parent - 1][bda->cur] == 1
			&& lda->e[bda->cur][bda->adj] == -1)))
			ret = 1;
		else if (!bda->cur_path && lda->e[bda->cur][bda->adj])
			ret = 1;
	}
	if (ret)
		bda->dead_end = 0;
	return (ret);
}

t_leminpath	*bfs(t_lemindata *lda)
{
	static t_bfsdata	bda = {0, NULL, NULL, NULL, 0, 0, NULL, 0};
	t_list				*ptr;

	init_bfsdata(&bda, lda);
	while (bda.first)
	{
		bda.dead_end = 1;
		if ((bda.cur = queue_popleft(&bda)) == lda->t)
			return (build_path(lda, bda.parent));
		ptr = lda->v[bda.cur]->adj;
		bda.cur_path = lda->v[bda.cur]->path;
		while (ptr)
		{
			bda.adj = *(int *)ptr->content;
			if (is_visitable(lda, &bda))
			{
				bda.parent[bda.adj] = bda.cur + 1;
				queue_append(&bda, bda.adj);
			}
			ptr = ptr->next;
		}
		if (bda.dead_end && bda.cur_path)
			bda.parent[bda.cur] = 0;
	}
	return (NULL);
}
