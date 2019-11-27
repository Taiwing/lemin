/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 08:58:47 by trponess          #+#    #+#             */
/*   Updated: 2019/11/27 22:09:15 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lemindata.h"
#include "lemin_options.h"

void ft_error(char *msg ,const char *line, int r)
{
	ft_dprintf(2,"ERROR > \nmsg:%s \nline:|%s| \ngnl:%d", msg,line, r);
	ft_exit(NULL, 1);
}

int is_int_num(const char *str)
{
	long long int nb;
	int i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] != '+')
		++i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (i > 10)
			return (0);
		++i;
	}
	nb = ft_atoi(str);
	if (nb > INT32_MAX || nb < INT32_MIN)
		return (0);
	return (1);
}

int is_room(const char *line)
{
	size_t		i;
	char	**p;
	int		nb_space;

	i = 0;
	nb_space = 0;
	p = ft_strsplit(line, ' ');//dont forget to free
	while (i < ft_strlen(line))
	{
		if (line[i] == ' ')
			++nb_space;
		++i;
	}
	if (nb_space > 2)
		return (0);
	if (ft_wtlen(p) == 3)
	{
		if (ft_strlen(p[0]) > 0 && !ft_strstr(p[0], "-") && is_int_num(p[1]) && is_int_num(p[2]))
		{
//			ft_printf("IS ROOM <%s>\n", line);
			return (1);
		}
	}
	return (0);
}

int is_link(const char *line)
{
	int		i;
	char	**p;

	i = 0;
	if (!line || ft_strstr(line, " "))
		return (0);
	p = ft_strsplit(line, '-');//tofree
	if (ft_wtlen(p) == 2)
	{
		if (ft_strlen(p[0]) > 0 && ft_strlen(p[1]) > 0 && p[0][0] != '#')
		{
//			ft_printf("IS LINK <%s>\n", line);
			return (1);
		}
	}
	return (0);
}

int is_comment(const char *line)
{
	if (!line)
		return (1);
	if (line[0] == '#')
	{
//		ft_printf("(comment) :<%s>\n", line);
		return (1);
	}
	return (0);
}

void check_first_int(t_lemindata *lda, char *line)
{
	t_list *t;
	int		r;

	while ((r = get_next_line(0, &line)) > 0)
	{
		if (is_int_num(line))
		{
//			ft_printf("1ST NON COMMENTLINE IS NUM :<%s>\n", line);	
			t = ft_lst_push_back(&(lda->map), NULL, 0);
			t->content = line;
			break;
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

void check_empty_start_L_space(const char *line, int r)
{
	if (!line)
		ft_error("empty line : ", line, r);
	if (line[0] == 'L')
		ft_error("start with L", line, r);
}	

int check_comment_room_link(t_lemindata *lda, const char *line, int r)
{
	static int fun_i;
	t_list *t;
	int (*check_fun[2])(const char *) = {&is_room, &is_link};

	if (!is_comment(line) && !check_fun[fun_i](line))
	{
		++fun_i;
		if (fun_i > 1 || !check_fun[fun_i](line))//CHECK LINK if room fails
			ft_error("not LINK/ROOM/COMMENT: ", line, r);
	}
	t = ft_lst_push_back(&(lda->map), NULL, 0);
	t->content = (void *)line;
	return (fun_i);
}

void check_double_start_end(t_lemindata *lda)
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

void check_roomis_start_end(t_lemindata *lda)
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

int	map_checker(t_lemindata *lda)
{	
	int		map_size;
	char	*line;
	int		r;
	int		f_i;
	
	map_size = 1; 
	line = NULL;
	check_first_int(lda, line);
	while ((r = get_next_line(0, &line)) > 0)
	{
		check_empty_start_L_space(line, r);	
		f_i = check_comment_room_link(lda, line, r);
		++map_size;
	}
	lda->map_size = map_size;
	if (r == -1)
		ft_error("ERROR gnl broke: LINE= ", line, r);
	if (f_i != 1)
		ft_error("ERROR file dont finish with links LINE:", line, r);
	check_double_start_end(lda);
	check_roomis_start_end(lda);
//	ft_printf("<<<<<<<<<<<end with MAP CHECKER>>>>>>>>>>>\n\n");
	return (0);
}
