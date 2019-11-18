/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:27:22 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 12:43:30 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lemindata.h"

void	set_path(t_leminpath *path, t_lemindata *lda,
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

void	del_path_node(void *content, size_t content_size)
{
	(void)content_size;
	ft_memdel((void **)&content);
}

void	destroy_path(t_lemindata *lda, t_leminpath **path)
{
	set_path(*path, lda, (int[2]){0, 0}, NULL);
	ft_listdel(&(*path)->nodes, del_path_node);
	ft_memdel((void **)path);
}

int		path_len_cmp(t_leminpath *p1, t_leminpath *p2)
{
	return (p1->len - p2->len);
}

void	add_path(t_lemindata *lda, t_list **solution, t_leminpath *path)
{
	t_list	*new;

	set_path(path, lda, (int[2]){0, -1}, path);
	new = ft_lstnew(NULL, 0);
	new->content = path;
	ft_lst_sorted_insert(solution, new, path_len_cmp);
}
