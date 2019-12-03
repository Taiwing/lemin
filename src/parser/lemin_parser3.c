/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parser3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:47:42 by trponess          #+#    #+#             */
/*   Updated: 2019/12/03 10:55:01 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lemindata.h"
#include "lemin_options.h"

void	check_empty_start_l_space(const char *line, int r)
{
	if (!line)
		ft_error("empty line : ", line, r);
	if (line[0] == 'L')
		ft_error("start with L", line, r);
}

int		check_comment_room_link(t_lemindata *lda, const char *line, int r)
{
	static int			fun_i;
	t_list				*t;
	static int			(*check_fun[2])(const char *) = {&is_room, &is_link};

	if (!is_comment(line) && !check_fun[fun_i](line))
	{
		++fun_i;
		if (fun_i > 1 || !check_fun[fun_i](line))
			ft_error("not LINK/ROOM/COMMENT: ", line, r);
	}
	t = ft_lst_push_back(&(lda->map), NULL, 0);
	t->content = (void *)line;
	return (fun_i);
}

void	check_double_start_end(t_lemindata *lda)
{
	int		i;
	char	*line;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	while (i < lda->map_size)
	{
		line = (char *)ft_lst_at(lda->map, i)->content;
		if (line && !ft_strcmp(line, "##start"))
			++start;
		if (line && !ft_strcmp(line, "##end"))
			++end;
		if (start > 1 || end > 1)
			ft_error("ERROR double start or end", line, -2);
		++i;
	}
	if (start == 0 || end == 0)
		ft_error("ERROR absent start or end", line, -2);
}

void	check_roomis_start_end(t_lemindata *lda)
{
	int		i;
	char	*line1;
	char	*line2;

	i = 0;
	while (i + 1 < lda->map_size)
	{
		line1 = (char *)ft_lst_at(lda->map, i)->content;
		line2 = (char *)ft_lst_at(lda->map, i + 1)->content;
		if (!ft_strcmp(line1, "##start") && !is_room(line2))
			ft_error("ERROR start is not a room", NULL, -2);
		if (!ft_strcmp(line1, "##end") && !is_room(line2))
			ft_error("ERROR end is not a room", NULL, -2);
		++i;
	}
}

void	check_first_int(t_lemindata *lda, char *line)
{
	t_list	*t;
	int		r;

	while ((r = get_next_line(0, &line)) > 0)
	{
		if (is_int_num(line))
		{
			t = ft_lst_push_back(&(lda->map), NULL, 0);
			t->content = line;
			break ;
		}
		else if (is_comment(line))
		{
			t = ft_lst_push_back(&(lda->map), NULL, 0);
			t->content = line;
		}
		else
			ft_error("ERROR don't start with INT", line, r);
	}
}
