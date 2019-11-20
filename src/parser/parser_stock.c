/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:37:38 by trponess          #+#    #+#             */
/*   Updated: 2019/11/20 17:51:09 by trponess         ###   ########.fr       */
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

void init_vertex(t_lemindata *lda, int map_size)
{
    int i = 0;

    lda->v = (t_vertex **)malloc(sizeof(t_vertex *) * map_size);
    ft_bzero(lda->v, sizeof(lda->v));
    while (i < map_size)
    {
        lda->v[i] = (t_vertex *)malloc(sizeof(t_vertex));
        ++i;
    }
}

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

void parser_stock(t_lemindata *lda)
{
    lda->antn = (long int)ft_lst_at(lda->map, 0)->content;
    int map_size = ft_lst_size(lda->map);
    lda->s = 0;

    int i = 1;
    int isstart = 0, isend = 0;

    init_vertex(lda, map_size);
    //t_vertex *v = (t_vertex *)malloc(sizeof(t_vertex) * map_size);//i dont know number of rooms
    while (i < map_size)
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

            

            lda->v[i]->name = ft_strdup(room_name);
            lda->v[i]->id = i;
            lda->v[i]->status = (isstart) ? SOURCE : NORMAL;
            lda->v[i]->status = (isend) ? SINK : NORMAL;
            //do adj after with links

        }
        if (is_link(line))
            break;
        ++i;
    }
    /*
    init_vertex(lda);
    int i = 0;int j = 0;
    while (i < map_size)
    {
        while (i < map_size)
        {
            t_list *n = ft_lst_at(lda->map, i);
            lda-> = n->content
            ++j;
        }
        j = 0;
        ++i;
    }*/



}