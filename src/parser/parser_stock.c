/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:37:38 by trponess          #+#    #+#             */
/*   Updated: 2019/11/25 16:22:36 by trponess         ###   ########.fr       */
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

	lda->v = (t_vertex **)ft_memalloc(sizeof(t_vertex *) * (lda->nb_rooms));
	//lda->v = (t_vertex **)malloc(sizeof(t_vertex *) * (lda->nb_rooms));
	while (i < lda->nb_rooms)
	{
		lda->v[i] = (t_vertex *)ft_memalloc(sizeof(t_vertex));    
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
		//ft_lstadd(&lda->v[i]->adj, ft_lstnew(NULL, 0));//causes 
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

	lda->e = (int **)ft_memalloc(sizeof(int *) * (lda->nb_rooms + 10000));
	while (i < lda->nb_rooms)
	{
		lda->e[i] = (int *)ft_memalloc(sizeof(int) * (lda->nb_rooms + 10000));
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


void stock_adjlist_and_e(t_lemindata *lda)
{
	if (!lda)
		return ;
	int i = 0;
	int size_map = ft_lst_size(lda->map);
	
	//t_vertex *v = (t_vertex *)malloc(sizeof(t_vertex) * map_size);//i dont know number of rooms
	while (i < size_map)
	{
		char *line = (char*)ft_lst_at(lda->map, i)->content;

		if (line && is_link(line))
		{
			
			char **rooms = ft_strsplit(line, '-');//tofree
			ft_printf("line %s is link -> cutting r1 %s r2 %s\n", line, rooms[0], rooms[1]);
			
			t_vertex *v1 = get_vertex_from_dict(lda, rooms[0]);
			t_vertex *v2 = get_vertex_from_dict(lda, rooms[1]);
			//if (!v1 || !v2 || !v1->adj || !v2->adj)
			//	return ;
			//v1->adj = ft_lstnew(NULL, 0);
			if (!v1)
				ft_printf("NOOOOO V1\n");
			if (!v2)
				ft_printf("NOOOOO V2\n");
			ft_printf("PLOP\n");
			t_list *x = ft_lst_push_back(&v1->adj, NULL, 0);
			t_list *y = ft_lst_push_back(&v2->adj, NULL, 0);
			ft_printf("PLOP2\n");
			if (!x || !y)
			{
				ft_printf("fucking X Y is EMPTY");
				return ;
			}
			//x->content = (int *)ft_memalloc(sizeof(int));
			//(int *)x->content[0] = v2->id;

		//!!if someone writes r1-r2 and r2-r1 it will be added twice everywhere
			x->content = &(v2->id);
			void *z = x->content;
			if (!z)
			{
				ft_printf("fucking z is EMPTY");
				return ;
			}
			ft_printf("adjecing adding %d\n", *(int *)z);
			y->content = &(v1->id);
			void *w = y->content;
			if (!w)
			{
				ft_printf("fucking w is EMPTY");
				return ;
			}
			ft_printf("adjecing adding %d\n", *(int *)w);


			//e 
			ft_printf("connecting %d %d\n", v1->id, v2->id);
			
			lda->e[v1->id][v2->id] = 1;
			lda->e[v2->id][v1->id] = 1;

			ft_printf("e success\n");

			if (!v1->adj)
				ft_printf("IS FUCKING EMPTY!!!\n");
			//else	
				//ft_printf("EXSIST>? %d -> \n", *(int *)(v1->adj->content));

			ft_printf("\n");
		}
		++i;
	}
	
}

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
			{
				lda->s = vi;
				lda->v[vi]->status = SOURCE;
			}
			if (isend)
			{
				lda->t = vi;
				lda->v[vi]->status = SINK;
			}


			//lda->v[vi]->status = (isstart == 1) ? SOURCE : NORMAL;
		   // lda->v[vi]->status = (isend) ? SINK : NORMAL;

			++vi;
			//do adj after with links

		}
		++i;
	}

	stock_v_in_dict(lda);
	init_edges(lda);
	stock_adjlist_and_e(lda);	
	//DISPLAY_DICTIONARY(lda);

	//get id id from v_dict[853(Oyt4)]
	//get_id from v_dict[853(K_u1)]

	//t_vertex *a = get_vertex_from_dict(lda, "Asa5");//start 
	//t_vertex *b = get_vertex_from_dict(lda, "Cfl8");//end
	DISPLAY_EDGED_NATRIX(lda);
	DISPLAY_ADJ_TABLE(lda);

	
	
	//(void)a;
	//(void)b;
}