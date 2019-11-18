/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lemindata.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:36:53 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 11:55:02 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LEMINDATA_H
# define T_LEMINDATA_H
# include "t_vertex.h"

typedef struct	s_lemindata
{
	int			options;
	int			ret;
	t_list		*map;
	long int	antn;
	int			vlen;
	t_vertex	**v;
	int			**e;
	int			s;
	int			t;
}				t_lemindata;

#endif
