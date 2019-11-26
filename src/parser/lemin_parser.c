/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:37:38 by trponess          #+#    #+#             */
/*   Updated: 2019/11/26 18:47:02 by trponess         ###   ########.fr       */
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


int is_num(const char *str)
{
	int i = 0;

	if (!str)
		return (0);
	if (str[0] == '-' || str[0] != '+')
		++i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}


int is_room(const char *line)
{
	//roomn N N\n
	if (!line)
		return (0);
	char **p = ft_strsplit(line, ' ');//dont forget to free
	if (ft_wtlen(p) == 3)
	{
		if (ft_strlen(p[0]) > 0 && is_num(p[1]) && is_num(p[2]))
		{
			ft_printf("IS ROOM <%s>\n", line);
			return (1);
		}
	}
	return (0);
}

int is_link(const char *line)
{
	//link N-N\n
	if (!line)
		return (0);
	if (ft_strstr(line, " "))
		return (0);
	char **p = ft_strsplit(line, '-');//tofree
	if (ft_wtlen(p) == 2)
	{
		if (ft_strlen(p[0]) > 0 && ft_strlen(p[1]) > 0 && ft_strcmp(p[0], p[1]) != 0)
		{
			ft_printf("IS LINK <%s>\n", line);
			return (1);
		}
	}
	return (0);
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
			
			t_list *x = ft_lst_push_back(&v1->adj, NULL, 0);
			t_list *y = ft_lst_push_back(&v2->adj, NULL, 0);
			
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

			if (!v1->adj)
				ft_printf("IS FUCKING EMPTY!!!\n");
			//else	
				//ft_printf("EXSIST>? %d -> \n", *(int *)(v1->adj->content));

			ft_printf("\n");
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


/*
int is_start(char *line, int *i)
{
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
}

void is_start_end(t_lemindata *lda, char *line, int *i, int *startend)
{
	int start;
	int end;
	

	start = ft_strcmp("##start", line);
	end = ft_strcmp("##end", line);

	if (start != 0 || end != 0)
		++(*i);
	if (start != 0)
	{
		*startend = 1;

	}
	else if (end != 0)
		*startend = 2;
	else 
		*startend = 0;
	
}
*/

/*
int		start_end_line(t_lemindata *lda, char o)
{
	static int	start_l;
	static int	end_l;
	int			i;
	char		*line;

	i = 0;
	if (!start_l)
	{
		while (i < lda->map_size)
		{
			line = (char*)ft_lst_at(lda->map, i)->content;
			if (!ft_strcmp("##start", line))
				start_l = i + 1;
			if (!ft_strcmp("##end", line))
				end_l = i + 1;
			if (start_l > 0 && end_l > 0)
				break;
			++i;
		}
	}
	return (o == 's' ? start_l : end_l);
}*/


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

	last_line = (char*)ft_lst_at(lda->map, li - 1)->content;
	if (!ft_strcmp("##start", last_line))
	{
		lda->s = vi;
		lda->v[vi]->status = SOURCE;
	}
	if (!ft_strcmp("##end", last_line))
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

void lemin_parser(t_lemindata *lda)
{
	stock_map(lda);
	lda->antn = (long int)ft_atoi(ft_lst_at(lda->map, 0)->content);//check for overflow	
	init_vertex_edges(lda);
	room_to_vertex(lda);

	//int i = 1;
	//int vi = 0;
	//int isstart = 0, isend = 0;
	//int startend = 0;

	


	/*int size_map = ft_lst_size(lda->map);
	while (i < size_map)
	{ft_printf("%d %d\n",i,  size_map);
		isstart = 0;
		isend = 0;
		char *line = (char*)ft_lst_at(lda->map, i)->content;
	
		is_start_end(lda, line, 
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
			++vi;
		}
		++i;
	}*/

//	stock_v_in_dict(lda);
//	init_edges(lda);
//	stock_adjlist_and_e(lda);	
	

	//get id id from v_dict[853(Oyt4)]
	//get_id from v_dict[853(K_u1)]

	//t_vertex *a = get_vertex_from_dict(lda, "Asa5");//start 
	//t_vertex *b = get_vertex_from_dict(lda, "Cfl8");//end

	//-----------test------------------------------
	//EEXECUTE IN ORDER
	DISPLAY_VERTEX(lda);
	//DISPLAY_DICTIONARY(lda);
	//DISPLAY_EDGED_NATRIX(lda);
	//DISPLAY_ADJ_TABLE(lda);
	DISPLAY_SIZE_INFO(lda);
	//-----------test------------------------------
	
	
	//(void)a;
	//(void)b;
}