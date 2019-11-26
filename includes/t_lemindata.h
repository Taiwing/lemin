/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lemindata.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:36:53 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/26 18:02:38 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LEMINDATA_H
# define T_LEMINDATA_H
# include "t_vertex.h"

#define HASH_SIZE 4096
typedef t_list *t_dict[HASH_SIZE];

//t_dict mydict;
//t_list *mydict[HASH_SIZE];

typedef struct		s_dict_elem
{
	const char		*key;
	const void			*val;//linkedlist of vertexes
}					t_dict_elem;

typedef struct	s_lemindata
{
	int			options;
	int			ret;
	t_list		*map;
	int			map_size;//everything init in this size
	int			nb_rooms;//not used
	int			nb_links;//not used
	long int	antn;
	int			vlen;
	t_vertex	**v;
	int			**e;
	int			s;
	int			t;
	t_dict		v_dict;
}				t_lemindata;

#endif
