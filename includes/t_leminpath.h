/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_leminpath.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:37:46 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/18 11:22:46 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LEMINPATH_H
# define T_LEMINPATH_H
# include "libft.h"

# define FORWARD	0
# define BACKWARD	1

typedef struct			s_leminpath
{
	t_list				*nodes;
	int					len;
	struct s_leminpath	*overlap;
}						t_leminpath;

#endif
