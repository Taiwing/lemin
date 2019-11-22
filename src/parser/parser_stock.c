/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:37:38 by trponess          #+#    #+#             */
/*   Updated: 2019/11/22 11:51:14 by trponess         ###   ########.fr       */
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
	return (hash % 10000);
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
/*
void stock_v_in_dict(t_lemindata *lda, int map_size)
{
    int i = 0;

    while (lda->v[i])
    {
        char *room_name = ft_strdup(lda->v[i]->name);
        lda->v_dict[hash_djb2(room_name)].key = ft_strdup(room_name);
        lda->v_dict[hash_djb2(room_name)].val = ft_lstnew(NULL, 0);
        ft_lst_push_front(lda->v_dict[hash_djb2(room_name)].val, lda->v[i],0);
        ++i;
    }
}
*/
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

    /*
    init_vertex(lda);
    int i = 0;int vi = 0;
    while (i < map_size)
    {
        while (i < map_size)
        {
            t_list *n = ft_lst_at(lda->map, i);
            lda-> = n->content
            ++vi;
        }
        vi = 0;
        ++i;
    }*/



}