/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 08:57:31 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/27 19:33:13 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_path.h"

static void	build_test_sol(t_list *src, t_list *dest, t_leminpath *to_add)
{
	while (src || to_add)
	{
		if (!to_add
			|| (src && ((t_leminpath *)src->content)->len < to_add->len))
		{
			dest->content = src->content;
			dest = dest->next;
		}
		else if (to_add)
		{
			dest->content = to_add;
			to_add = NULL;
		}
		if (src)
			src = src->next;
	}
}

static int	count_turns(t_list *solution, int len, int n)
{
	int		turns;
	int		maxl;

	maxl = ((t_leminpath *)solution->content)->len;
	turns = maxl - 1;
	while (solution && n > 0)
	{
		n -= maxl + 1 - ((t_leminpath *)solution->content)->len;
		solution = solution->next;
	}
	if (n > 0)
	{
		turns += n / len;
		if (n % len)
			++turns;
	}
	return (turns);
}

int			test_solution(t_list *solution, t_leminpath *to_add, int antn)
{
	static t_list	*test_sol = NULL;
	static int		len = 0;
	int				new_len;
	t_list			*ptr;
	
	if (len)
	{
		ptr = test_sol;
		while (ptr)
		{
			ptr->content = NULL;
			ptr = ptr->next;
		}
	}
	new_len = ft_lst_size(solution) + !!to_add;
	while (len < new_len)
	{
		ft_lst_push_front(&test_sol, NULL, 0);
		++len;
	}
	build_test_sol(solution, test_sol, to_add);
	ft_lst_reverse(&test_sol);
	return (count_turns(test_sol, new_len, antn));
}
