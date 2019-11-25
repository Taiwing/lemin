/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:37:38 by trponess          #+#    #+#             */
/*   Updated: 2019/11/25 10:35:54 by trponess         ###   ########.fr       */
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

static void init_vertex(t_lemindata *lda)
{
	int i = 0;

	lda->v = (t_vertex **)ft_secmalloc(sizeof(t_vertex *) * (lda->nb_rooms));
	//lda->v = (t_vertex **)malloc(sizeof(t_vertex *) * (lda->nb_rooms));
	while (i < lda->nb_rooms)
	{
		lda->v[i] = (t_vertex *)ft_secmalloc(sizeof(t_vertex));    
		//lda->v[i] = (t_vertex *)malloc(sizeof(t_vertex));
		lda->v[i]->id = -1;
		++i;
	}
}

void stock_v_in_dict(t_lemindata *lda)
{
	int i = 0;

	ft_bzero(lda->v_dict, sizeof(t_dict));
	while (i < lda->nb_rooms)
	{
		int key_nb = hash_djb2(lda->v[i]->name);
		
		t_dict_elem d;
		d.key = lda->v[i]->name;
		d.val = lda->v[i];
		ft_lst_push_back(&lda->v_dict[key_nb], &d,sizeof(t_dict_elem));
		
//-----------TEST-----------------
/*int nb_elem = 0;
int max = ft_lst_size(lda->v_dict[key_nb]);
ft_printf("-----v_dict[%d]---------\n", key_nb);
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
ft_printf("-----DONE-----------\n");*/
//------------------------------
		++i;
	}
}

void DISPLAY_DICTIONARY(t_lemindata *lda)//need nb_rooms, dict
{
	int i = 0;

	while (i < lda->nb_rooms)
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

t_dict_elem *search_for_dict_elem(t_lemindata *lda, char *room)
{
		int key_nb = hash_djb2(room);
		int nb_elem = 0;
		int max = ft_lst_size(lda->v_dict[key_nb]);
		while (nb_elem < max)
		{
			t_dict_elem *x = (t_dict_elem*)ft_lst_at(lda->v_dict[key_nb], nb_elem)->content;
			const char *k = x->key;
			if (!ft_strcmp(room, k))
				return (x);
			nb_elem++;
		}
		return (NULL);
}

void init_edges(t_lemindata *lda)
{
	int i = 0;

	lda->e = (int **)ft_memalloc(sizeof(int *) * (lda->nb_rooms));
	while (i < lda->nb_rooms)
	{
		lda->e[i] = (int *)ft_memalloc(sizeof(int) * 2);
		++i;
	}	
}

t_vertex *get_vertex_from_dict(t_lemindata *lda, char *room)
{
	ft_printf("getting dict_elem_value vertex in dict name <%s> ....\n", room);
	t_list *elem_list = (t_list *)lda->v_dict[hash_djb2(room)];
	if (!elem_list)
	{
		ft_printf("hash room not in dict\n");
		return (0);
	}
	t_dict_elem *d = search_for_dict_elem(lda, room); 
	if (!d)
	{
		ft_printf("FOUND EXCEPTION>>>>>>>>>>>>the key wasnt found dict\n");
		return (0);
	}
	t_vertex *z = (t_vertex*)d->val;
	ft_printf("			!!!found name:%s id:%d status:%d\n",z->name, z->id, z->status); 
	return ((t_vertex *)d->val);
}

/*
void stock_adjlist_and_e(t_lemindata *lda)
{
	int i = 0;
	//ft_bzero(lda->v_dict, sizeof(t_dict));
	int size_map = ft_lst_size(lda->map);
	//t_vertex *v = (t_vertex *)malloc(sizeof(t_vertex) * map_size);//i dont know number of rooms
	
	while (i < size_map)
	{
		char *line = (char*)ft_lst_at(lda->map, i)->content;

		if (is_link(line))
		{
			char **p = ft_strsplit(line, '-');//tofree
			char *room1 = p[1];
			char *room2 = p[2];
			//int key_nb1 = hash_djb2(room1);
			//int key_nb2 = hash_djb2(room2);

			//ft_lst_push_back(&lda->v_dict[key_nb], &d,sizeof(t_dict_elem));
			t_list *adj = lda->v_dict[hash_djb2(room1)]->content->val->adj;

			t_list *x = ft_lst_push_back(&adj, NULL, 0);
			x->content  = ft_strdup(room2);

			t_list *keys_list = (t_list *)lda->v_dict[hash_djb2(room1)];
			t_list *key = ft_lst_find(keys_list, room1, &ft_strcmp);
			t_vertex *v = (t_vertex *)key->content->val;
			int id1 = v->id;

			t_list *keys_list = (t_list *)lda->v_dict[hash_djb2(room2)];
			t_list *key = ft_lst_find(keys_list, room2, &ft_strcmp);
			t_vertex *v = (t_vertex *)key->content->val;
			int id2 = v->id;

			lda->e[id1][id2] = 1;
			lda->e[id2][id1] = 1;




		}
	}
	
}
*/
void parser_stock(t_lemindata *lda)
{
	lda->antn = (long int)ft_atoi(ft_lst_at(lda->map, 0)->content);	
	lda->vlen = lda->nb_rooms;
	lda->s = 0;

	int i = 1;
	int vi = 0;
	int isstart = 0, isend = 0;

	init_vertex(lda);
	int size_map = ft_lst_size(lda->map);
	//t_vertex *v = (t_vertex *)malloc(sizeof(t_vertex) * map_size);//i dont know number of rooms
	while (i < size_map)
	{
		isstart = 0;
		isend = 0;
		char *line = (char*)ft_lst_at(lda->map, i)->content;

		if (!ft_strcmp("##start", line))
		{
			++i;
			line = (char*)ft_lst_at(lda->map, i)->content;
			isstart = 1;
		}
		if (!ft_strcmp("##end", line))
		{
			++i;
			line = (char*)ft_lst_at(lda->map, i)->content;
			isend = 1;
		}
		if (is_room(line))
		{
			char *room_name = ft_split_whitespaces(line)[0];//watch out for leaks

			lda->v[vi]->name = ft_strdup(room_name);
			lda->v[vi]->id = vi;
			lda->v[vi]->status = NORMAL;
			if (isstart)
				lda->v[vi]->status = SOURCE;
			if (isend)
				lda->v[vi]->status = SINK;


			//lda->v[vi]->status = (isstart == 1) ? SOURCE : NORMAL;
		   // lda->v[vi]->status = (isend) ? SINK : NORMAL;

			++vi;
			//do adj after with links

		}
		++i;
	}

	stock_v_in_dict(lda);
	init_edges(lda);
	//DISPLAY_DICTIONARY(lda);

	//get id id from v_dict[853(Oyt4)]
	//get_id from v_dict[853(K_u1)]

	t_vertex *a = get_vertex_from_dict(lda, "Asa5");
	t_vertex *b = get_vertex_from_dict(lda, "Cfl8");

	
	(void)a;
	(void)b;
}