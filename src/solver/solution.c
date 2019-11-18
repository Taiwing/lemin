/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:06:26 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 19:08:41 by yforeau          ###   ########.fr       */
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
