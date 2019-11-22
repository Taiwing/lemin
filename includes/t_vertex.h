/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vertex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:43:54 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/22 11:06:21 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_VERTEX_H
# define T_VERTEX_H

# include "libft.h"

enum				e_status {NORMAL, SOURCE, SINK};

typedef struct		s_vertex
{
	t_list			*adj;
	enum e_status	status;
	char			*name;
	//t_leminpath				*path;//maybe replace this by a pointer to a path
	int				id;
}					t_vertex;

#endif
