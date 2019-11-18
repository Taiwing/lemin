/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vertex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:43:54 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 10:38:30 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_VERTEX_H
# define T_VERTEX_H

# include "t_leminpath.h"

enum				e_status {NORMAL, SOURCE, SINK};

typedef struct		s_vertex
{
	t_list			*adj;
	enum e_status	status;
	char			*name;
	t_leminpath		*path;
}					t_vertex;

#endif
