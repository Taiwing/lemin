/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lemin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:54:20 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/28 17:48:30 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_options.h"
#include "print_lemin.h"

static int	move_ants(t_lemindata *lda, t_ant *ant,
				t_list *solution, int *moving)
{
	int	i;
	int	arrived;

	i = -1;
	arrived = 0;
	while (++i < lda->antn)
	{
		if (ant[i].state == INACTIVE && solution
			&& ((t_leminpath *)solution->content)->len <= lda->turns)
		{
			ant[i].room = ((t_leminpath *)solution->content)->nodes;
			solution = solution->next;
			ant[i].state = MOVING;
		}
		if (ant[i].state == MOVING && (!(ant[i].room = ant[i].room->next)))
		{
			ant[i].state = ARRIVED;
			++arrived;
		}
		else if (ant[i].state == MOVING)
			++(*moving);
	}
	return (arrived);
}

static void	print_solution(t_lemindata *lda, t_list *solution)
{
	t_ant	*ant;
	int		moving;
	int		n;
	int		i;
	
	n = lda->antn;
	ant = ft_memalloc(n * sizeof(t_ant));
	while (n)
	{
		moving = 0;
		n -= move_ants(lda, ant, solution, &moving);
		i = -1;
		while (n && ++i < lda->antn)
		{
			if (ant[i].state == MOVING)
				ft_printf("L%d-%s%c", i + 1,
					lda->v[*(int *)ant[i].room->content]->name,
					--moving ? ' ' : '\n');
		}
		--lda->turns;
	}
}

static void	print_map(t_list *map)
{
	while (map)
	{
		ft_printf("%s\n", (char *)map->content);
		map = map->next;
	}
	ft_printf("\n");
}
void		print_lemin(t_lemindata *lda, t_list *solution)
{
	int	turns;

	if (solution)
	{
		turns = lda->turns;
		if (!(lda->options & (O_SOLUTION | O_EXPLAINED)))
			print_map(lda->map);
		if (lda->options & O_EXPLAINED)
			explain_final_solution(lda, solution);
		else
			print_solution(lda, solution);
		if (lda->options & O_SOLUTION)
			ft_printf("# Map solved in %d turns.\n", turns);
	}
	else
		ft_printf("No solution :(\n");
}
