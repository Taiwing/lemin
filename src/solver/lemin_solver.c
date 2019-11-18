/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_solver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:47:21 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 12:43:39 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_path.h"

static int	get_maxflow(t_lemindata *lda)
{
	int	maxflow;
	int	t_adjlen;

	maxflow = ft_lst_size(lda->v[lda->s]->adj);
	t_adjlen = ft_lst_size(lda->v[lda->t]->adj);
	maxflow = t_adjlen < maxflow ? t_adjlen : maxflow;
	maxflow = lda->antn < maxflow ? lda->antn : maxflow;
	return (maxflow);
}

void		lemin_solver(t_lemindata *lda, t_list **solution)
{
	int			turns;
	int			new_turns;
	int			flow;
	int			maxflow;
	t_leminpath	*path;

	turns = -1;
	flow = 0;
	maxflow = get_maxflow(lda);
	path = NULL;
	while (flow < maxflow)
	{
		if (!(path = bfs(lda)))
			break ;
		new_turns = path->overlap ? fix_overlap(lda, &path, solution, turns) :
			test_new_solution(*solution, path, lda->antn);
		if (new_turns < turns || turns == -1)
		{
			turns = new_turns;
			add_path(lda, solution, path);
			++flow;
		}
		else if (!path->overlap)
			destroy_path(lda, &path);
	}
}
