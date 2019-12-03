/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:37:38 by trponess          #+#    #+#             */
/*   Updated: 2019/12/03 10:09:38 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lemindata.h"
#include "lemin_options.h"

unsigned long	hash_djb2(void *ptr)
{
	unsigned char	*str;
	unsigned long	hash;
	int				c;

	str = (unsigned char*)ptr;
	hash = 5381;
	while ((c = *str++))
		hash += (hash << 5) + c;
	return (hash % HASH_SIZE);
}

t_vertex		*get_vertex_from_dict(t_lemindata *lda, char *room)
{
	int			key_nb;
	int			max;
	int			nb_elem;
	t_dict_elem	*x;

	key_nb = hash_djb2(room);
	nb_elem = 0;
	max = ft_lst_size(lda->v_dict[key_nb]);
	while (nb_elem < max)
	{
		x = (t_dict_elem*)ft_lst_at(lda->v_dict[key_nb], nb_elem)->content;
		if (!ft_strcmp(room, x->key))
			return ((t_vertex *)x->val);
		nb_elem++;
	}
	return (NULL);
}

void			init_vertex_edges(t_lemindata *lda)
{
	int i;

	i = 0;
	lda->v = (t_vertex **)ft_memalloc(sizeof(t_vertex *) * (lda->map_size));
	lda->e = (int **)ft_memalloc(sizeof(int *) * (lda->map_size));
	while (i < lda->map_size)
	{
		lda->v[i] = (t_vertex *)ft_memalloc(sizeof(t_vertex));
		lda->e[i] = (int *)ft_memalloc(sizeof(int) * (lda->map_size));
		++i;
	}
}

void			ft_error(char *msg, const char *line, int r)
{
	ft_dprintf(2, "ERROR > \nmsg:%s \nline:|%s| \ngnl:%d", msg, line, r);
	ft_exit(NULL, 1);
}

int				lemin_parser(t_lemindata *lda)
{
	map_checker(lda);
	lda->antn = (long int)ft_atoi(ft_lst_at(lda->map, 0)->content);
	init_vertex_edges(lda);
	room_to_vertex(lda);
	stock_vertex_lst_in_dict(lda);
	stock_adjlist_and_e(lda);
	return (0);
}
