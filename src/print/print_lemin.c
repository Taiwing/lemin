/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lemin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:54:20 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/27 22:40:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_options.h"
#include "print_lemin.h"

static int	move_ants(t_ant *ant, t_list *solution, int len, int *moving)
{
	int	i;
	int	arrived;

	i = -1;
	arrived = 0;
	while (++i < len)
	{
		if (ant[i].state == INACTIVE && solution)
		{
			ant[i].room = ((t_leminpath *)solution->content)->nodes->next;
			solution = solution->next;
			ant[i].state = MOVING;
			++(*moving);
		}
		else if (ant[i].state == MOVING)
		{
			if (!(ant[i].room = ant[i].room->next))
			{
				ant[i].state = ARRIVED;
				++arrived;
			}
			*moving = ant[i].state == MOVING ? *moving + 1 : *moving;
		}
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
		n -= move_ants(ant, solution, lda->antn, &moving);
		i = -1;
		while (n && ++i < lda->antn)
		{
			if (ant[i].state == MOVING)
				ft_printf("L%d-%s%c", i + 1,
					lda->v[*(int *)ant[i].room->content]->name,
					--moving ? ' ' : '\n');
		}
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

void		print_lemin(t_lemindata *lda, t_list *solution, int turns)
{
	if (solution)
	{
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
