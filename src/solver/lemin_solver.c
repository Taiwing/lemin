/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_solver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:47:21 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/19 15:17:30 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_path.h"
#include "solution.h"
#include "bfs.h"
#include "fix_overlap.h"
#include "lemin_options.h"

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

static int	augmenting_path(t_lemindata *lda, t_leminpath **path,
				t_list **solution, int *turns)
{
	t_leminpath	*overlap;
	int			new_turns;

	if((overlap = (*path)->overlap))
		new_turns = fix_overlap(lda, path, solution, *turns);
	else
		new_turns = test_solution(*solution, *path, lda->antn); 
	if (new_turns < *turns || *turns == -1)
	{
		if (!overlap)
			explain_path(lda, *path);
		explain_solution(lda, *turns, new_turns);
		*turns = new_turns;
		return (1);
	}
	return (0);
}

t_list		*lemin_solver(t_lemindata *lda, int *turns)
{
	int			flow;
	int			maxflow;
	t_leminpath	*path;
	t_list		*solution;

	flow = 0;
	solution = NULL;
	maxflow = get_maxflow(lda);
	while (flow < maxflow)
	{
		if (!(path = bfs(lda)))
			break ;
		if (augmenting_path(lda, &path, &solution, turns))
		{
			add_path(lda, &solution, path);
			++flow;
		}
		else if (!path->overlap)
			destroy_path(lda, &path);
	}
	return (solution);
}
