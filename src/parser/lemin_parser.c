/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:37:38 by trponess          #+#    #+#             */
/*   Updated: 2019/11/27 22:06:29 by yforeau          ###   ########.fr       */
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



void DISPLAY_DICTIONARY(t_lemindata *lda)//need nb_rooms, dict
{
	int i = 0;

	while (i < lda->vlen)
	{
		int key_nb = hash_djb2(lda->v[i]->name);
		int nb_elem = 0;
		int max = ft_lst_size(lda->v_dict[key_nb]);
		ft_printf("-----v_dict[%d] for vertex room %s---------\n", key_nb, lda->v[i]->name);
		while (nb_elem < max)
		{
			t_dict_elem *x = (t_dict_elem*)ft_lst_at(lda->v_dict[key_nb], nb_elem)->content;
			const char *k = x->key;
			t_vertex *v = (t_vertex *)x->val;
			ft_printf("content of lda->v_dict[%d(%s)] elem %d : key <%s> val-vertex:[roomname]<%s> [id]<%d> [status]<%d>\n", \
					key_nb,k, nb_elem,\
					k, v->name, v->id, v->status);
			nb_elem++;
			
		}
		ft_printf("-----DONE-----------\n");
		++i;
	}
}

void DISPLAY_SIZE_INFO(t_lemindata *l)
{
	ft_printf("\nT_LEMINDATA\n:[ret]<%s>\n[map_size]<%d>\n[nb_links]<%d>\n[antn]<%d>\n[vlen]<%d>\n[s]<%d>\n[t]<%d>\n", \
	l->ret, l->map_size, l->nb_links, l->antn, l->vlen, l->s, l->t);
}

void DISPLAY_EDGED_NATRIX(t_lemindata *d)
{
	int y = 0;
    int x = 0;
    int i = 0;
   
   if (!d->e)
   {
	   ft_printf(">>>EDGES EMPTY\n");
	   return ;
   }
    ft_printf("\n");
    i = 0;
    while (y < d->vlen)
    {
        //printf("%s        ", rooms[y]);
        while (x < d->vlen)
        {
            ft_printf("%d ", d->e[y][x]);
            ++x;
        }
        ft_printf("\n");
        //printf("%d", matrix[i]);
        x = 0;
        ++y;
    }
}

void DISPLAY_ADJ_TABLE(t_lemindata *lda)
{
	int i = 0;
	int j = 0;
	while (i < lda->vlen)
	{
		ft_printf("\nvertex:[roomname]<%s>[id]<%d>", lda->v[i]->name, lda->v[i]->id);
		ft_printf("ADJ LIST : ");
		t_list *cadj = lda->v[i]->adj;
		if (!cadj)
		{
			ft_printf("IS EMPTY!!!\n");
			return ;
		}
		int size = ft_lst_size(cadj);
		while (j < size)
		{
			t_list *c = ft_lst_at(cadj, j);
			void *z = c->content;
			if (!z)
			{
				ft_printf("content S EMPTY!!!\n");
				return ;
			}
			ft_printf(" %d -> ", *(int *)z);
			++j;
		}
		
		j = 0;
		++i;
	}
	ft_printf("\n");
}

void DISPLAY_VERTEX(t_lemindata *lda)
{
	int i = 0;
	while (i < lda->vlen)
	{
		ft_printf("\nvertex %d:\n[roomname]<%s>\n[id]<%d>\n[status]%d\n[adj]notset\n\n",i, lda->v[i]->name, lda->v[i]->id, lda->v[i]->status);
		++i;
	}
	ft_printf("\n");
}

t_vertex *get_vertex_from_dict(t_lemindata *lda, char *room)
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


void stock_adjlist_and_e(t_lemindata *lda)
{
	int		i;
	char	*line;
	char	**rooms;
	t_vertex *v[2];
	t_list	*adj[2];

	i = 0;
	while (i < lda->map_size)
	{
		line = (char*)ft_lst_at(lda->map, i)->content;
		if (is_link(line))
		{
			rooms = ft_strsplit(line, '-');//tofree
				//ft_printf("line %s is link -> cutting r1 %s r2 %s\n", line, rooms[0], rooms[1]);
			v[0] = get_vertex_from_dict(lda, rooms[0]);
			v[1] = get_vertex_from_dict(lda, rooms[1]);
			adj[0] = ft_lst_push_back(&v[0]->adj, NULL, 0);
			adj[1] = ft_lst_push_back(&v[1]->adj, NULL, 0);
			adj[0]->content = &(v[1]->id);
			adj[1]->content = &(v[0]->id);
				//ft_printf("adjecing adding %d\n", *(int *)adj[0]->content);
				//ft_printf("adjecing adding %d\n", *(int *)adj[1]->content);
				//ft_printf("connecting %d %d\n", v[0]->id, v[1]->id);
			lda->e[v[0]->id][v[1]->id] = 1;
			lda->e[v[1]->id][v[0]->id] = 1;
		}
		++i;
	}
}

void stock_map(t_lemindata *lda)
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
	ft_printf("line <%s>\n", (char *)ptr->content);
	}
	lda->map_size = map_size;
}

void DISPLAY_MAP(t_lemindata *lda)
{
	int	i = 0;
	char *line;
	while (i < lda->map_size)
	{
		line = (char *)ft_lst_at(lda->map, i)->content;
		ft_printf("line <%s>\n", line);
		++i;
	}
}


void init_vertex_edges(t_lemindata *lda)
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

void is_start_end(t_lemindata *lda, int li, int vi)
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


void room_to_vertex(t_lemindata *lda)
{
	int		vi;
	int		li;
	char	*line;
	char	*room_name;

	vi = 0;
	li = 0;
	while (li < lda->map_size)
	{
		line = (char*)ft_lst_at(lda->map, li)->content;
		if (is_room(line))
		{
			room_name = ft_split_whitespaces(line)[0];
			lda->v[vi]->name = room_name;
			lda->v[vi]->id = vi;
			is_start_end(lda, li, vi);
			++vi;
		}
		++li;
	}
	lda->vlen = vi;
}

void	stock_vertex_lst_in_dict(t_lemindata *lda)
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

int  lemin_parser(t_lemindata *lda)
{
	//stock_map(lda);
	map_checker(lda);
	lda->antn = (long int)ft_atoi(ft_lst_at(lda->map, 0)->content);//check for overflow	
	init_vertex_edges(lda);
	room_to_vertex(lda);
	stock_vertex_lst_in_dict(lda);
	stock_adjlist_and_e(lda);
/*

//	stock_v_in_dict(lda);
//	init_edges(lda);
//	stock_adjlist_and_e(lda);	
	

	//get id id from v_dict[853(Oyt4)]
	//get_id from v_dict[853(K_u1)]

	//maps/Sample_maps/big/generator--big_round_01
	t_vertex *a = get_vertex_from_dict(lda, "Asa5");//start 
	t_vertex *b = get_vertex_from_dict(lda, "Cfl8");//end
	if (a && b)
	{
	ft_printf("\nvertex %c:\n[roomname]<%s>\n[id]<%d>\n[status]%d\n[adj]notset\n\n",'a', a->name, a->id, a->status);
	ft_printf("\nvertex %c:\n[roomname]<%s>\n[id]<%d>\n[status]%d\n[adj]notset\n\n",'b', b->name, b->id, b->status);
	}


	//-----------test------------------------------
	//EEXECUTE IN ORDER
	DISPLAY_MAP(lda);
	DISPLAY_VERTEX(lda);
	DISPLAY_DICTIONARY(lda);
	//DISPLAY_EDGED_NATRIX(lda);
	DISPLAY_ADJ_TABLE(lda);
	DISPLAY_SIZE_INFO(lda);
	//-----------test------------------------------
	

	//(void)a;
	//(void)b;
*/
	return (0);
}
