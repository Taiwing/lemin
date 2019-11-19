/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:13:41 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/19 14:38:58 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_options.h"

static void	print_path(t_lemindata *lda, t_leminpath *path)
{
	t_list	*ptr;

	ptr = path->nodes;
	while (ptr)
	{
		ft_printf("%s%c", lda->v[*(int *)ptr->content]->name,
			ptr->next ? '-' : '\n');
		ptr = ptr->next;
	}
}

void		explain_path(t_lemindata *lda, t_leminpath *path)
{
	if ((lda->options & O_EXPLAINED) && !(lda->options & O_SOLUTION))
	{
		ft_printf("Found new AUGMENTING PATH:\n");
		print_path(lda, path);
	}
}

void		explain_split(t_lemindata *lda, t_leminpath *path,
				t_leminpath *overlap_path, t_leminpath *split[2])
{
	explain_path(lda, path);
	if ((lda->options & O_EXPLAINED) && !(lda->options & O_SOLUTION))
	{
		ft_printf("Split path:\n");
		ft_printf("Cut edges: ");
		print_path(lda, overlap_path);
		ft_printf("First part: ");
		print_path(lda, split[0]);
		ft_printf("Second part: ");
		print_path(lda, split[0]);
	}
}

void		explain_solution(t_lemindata *lda, int turns, int new_turns)
{
	if ((lda->options & O_EXPLAINED) && !(lda->options & O_SOLUTION))
	{
		if (turns == -1)
			ft_printf("Found first solution in %d turns.\n", new_turns);
		else
			ft_printf("Old solution: %d turns\nNew solution: %d turns\n",
				turns, new_turns);
	}
}
