/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:37:38 by trponess          #+#    #+#             */
/*   Updated: 2019/11/22 17:02:22 by trponess         ###   ########.fr       */
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

/*
void init_adj_list(t_lemindata *lda)
{
	int i = 0;

	ft_bzero(lda->v_dict, sizeof(t_dict));
	while (i < lda->nb_rooms)
	{

	}
	
}*/

void parser_stock(t_lemindata *lda)
{
	lda->antn = (long int)ft_atoi(ft_lst_at(lda->map, 0)->content);	
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
		if (is_link(line))
			break;
		++i;
	}

	stock_v_in_dict(lda);

	DISPLAY_DICTIONARY(lda);

	



}