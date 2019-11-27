/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:06:26 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/19 09:24:06 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_path.h"

void		add_path(t_lemindata *lda, t_list **solution, t_leminpath *path)
{
	t_list	*new;

	set_path(path, lda, (int[2]){0, -1}, path);
	new = ft_lstnew(NULL, 0);
	new->content = path;
	ft_lst_sorted_insert(solution, new, path_len_cmp);
}

static int	ptr_cmp(void *p1, void *p2)
{
	return (p1 != p2);
}

void		replace_path(t_list **solution, t_leminpath *orig, t_leminpath *new)
{
	t_list	*ptr;

	ft_lst_remove_if(solution, orig, ptr_cmp);
	ptr = ft_lstnew(NULL, 0);
	ptr->content = new;
	ft_lst_sorted_insert(solution, ptr, path_len_cmp);
}
