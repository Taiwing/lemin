/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lemindata.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:02:38 by trponess          #+#    #+#             */
/*   Updated: 2019/12/03 10:54:22 by trponess         ###   ########.fr       */
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
	int			turns;
	t_dict		v_dict;
}				t_lemindata;

void			room_to_vertex(t_lemindata *lda);
void			stock_vertex_lst_in_dict(t_lemindata *lda);
void			stock_adjlist_and_e(t_lemindata *lda);
unsigned long	hash_djb2(void *ptr);
t_vertex		*get_vertex_from_dict(t_lemindata *lda, char *room);


void			stock_adjlist_and_e(t_lemindata *lda);
void			stock_map(t_lemindata *lda);
void			is_start_end(t_lemindata *lda, int li, int vi);
void			room_to_vertex(t_lemindata *lda);
void			stock_vertex_lst_in_dict(t_lemindata *lda);

unsigned long	hash_djb2(void *ptr);
t_vertex		*get_vertex_from_dict(t_lemindata *lda, char *room);
void			init_vertex_edges(t_lemindata *lda);
void			ft_error(char *msg, const char *line, int r);
int				lemin_parser(t_lemindata *lda);

void	check_empty_start_l_space(const char *line, int r);
int		check_comment_room_link(t_lemindata *lda, const char *line, int r);
void	check_double_start_end(t_lemindata *lda);
void	check_roomis_start_end(t_lemindata *lda);
void	check_first_int(t_lemindata *lda, char *line);

int		is_int_num(const char *str);
int		is_room(const char *line);
int		is_link(const char *line);
int		is_comment(const char *line);
int		map_checker(t_lemindata *lda);


#endif
