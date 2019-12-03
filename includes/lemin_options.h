/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_options.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:03:43 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/03 13:03:54 by yforeau          ###   ########.fr       */
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
int		is_room(const char *line);
int		is_link(const char *line);
int		map_checker(t_lemindata *lda);

void	help(char *name);
void	explain_split(t_lemindata *lda, t_leminpath *path,
				t_leminpath *overlap_path, t_leminpath *split[2]);
void	explain_path(t_lemindata *lda, t_leminpath *path);
void	explain_solution(t_lemindata *lda, int new_turns);
void	explain_final_solution(t_lemindata *lda, t_list *solution);

#endif
