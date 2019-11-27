/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_options.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:44:21 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/27 14:05:17 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_OPTIONS_H
# define LEMIN_OPTIONS_H
# include "t_lemindata.h"

# define OPT_COUNT			4

# define O_HELP				0x01
# define O_ANTS				0x02
# define O_SOLUTION			0x04
# define O_EXPLAINED		0x08

# define OPTSTRING			"ha:se"

void	get_lemin_options(t_lemindata *lda, int argc, char **argv);
int is_room(const char *line);
int is_link(const char *line);
int	map_checker(t_lemindata *lda);

#endif
