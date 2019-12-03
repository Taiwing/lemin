/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:37:38 by trponess          #+#    #+#             */
/*   Updated: 2019/12/03 10:08:42 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lemindata.h"
#include "lemin_options.h"

void			stock_adjlist_and_e(t_lemindata *lda)
{
	int			i;
	char		*line;
	char		**rooms;
	t_vertex	*v[2];
	t_list		*adj[2];

	i = 0;
	while (i < lda->map_size)
	{
		line = (char*)ft_lst_at(lda->map, i)->content;
		if (is_link(line))
		{
			rooms = ft_strsplit(line, '-');
			v[0] = get_vertex_from_dict(lda, rooms[0]);
			v[1] = get_vertex_from_dict(lda, rooms[1]);
			adj[0] = ft_lst_push_back(&v[0]->adj, NULL, 0);
			adj[1] = ft_lst_push_back(&v[1]->adj, NULL, 0);
			adj[0]->content = &(v[1]->id);
			adj[1]->content = &(v[0]->id);
			lda->e[v[0]->id][v[1]->id] = 1;
			lda->e[v[1]->id][v[0]->id] = 1;
		}
		++i;
	}
}

void			stock_map(t_lemindata *lda)
{
	char	*line;
	int		r;
	int		map_size;
	t_list	*ptr;

	map_size = 0;
	while ((r = get_next_line(0, &line)) > 0)
	{
		ptr = ft_lst_push_back(&(lda->map), NULL, 0);
		ptr->content = line;
		++map_size;
	}
	lda->map_size = map_size;
}

void			is_start_end(t_lemindata *lda, int li, int vi)
{
	char	*last_line;

	last_line = NULL;
	if (li - 1 > 0)
		last_line = (char *)ft_lst_at(lda->map, li - 1)->content;
	if (last_line && !ft_strcmp("##start", last_line))
	{
		lda->s = vi;
		lda->v[vi]->status = SOURCE;
	}
	if (last_line && !ft_strcmp("##end", last_line))
	{
		lda->t = vi;
		lda->v[vi]->status = SINK;
	}
}

void			room_to_vertex(t_lemindata *lda)
{
	int		vi;
	int		li;
	char	*line;

	vi = 0;
	li = 0;
	while (li < lda->map_size)
	{
		line = (char*)ft_lst_at(lda->map, li)->content;
		if (is_room(line))
		{
			lda->v[vi]->name = ft_strndup(line, ft_strchr(line, ' ') - line);
			lda->v[vi]->id = vi;
			is_start_end(lda, li, vi);
			++vi;
		}
		++li;
	}
	lda->vlen = vi;
}

void			stock_vertex_lst_in_dict(t_lemindata *lda)
{
	int				i;
	int				key_nb;
	t_dict_elem		d;

	i = 0;
	ft_bzero(lda->v_dict, sizeof(t_dict));
	while (i < lda->vlen)
	{
		key_nb = hash_djb2(lda->v[i]->name);
		d.key = lda->v[i]->name;
		d.val = lda->v[i];
		ft_lst_push_back(&lda->v_dict[key_nb], &d, sizeof(t_dict_elem));
		++i;
	}
}
