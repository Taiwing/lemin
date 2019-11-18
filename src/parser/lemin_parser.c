/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 08:58:47 by trponess          #+#    #+#             */
/*   Updated: 2019/11/18 16:40:28 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lemindata.h"
#include "lemin_options.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
int check_line(const char *cur_line)
{
	static int first;

	if (!first && ft_isdigit(ft_atoi(cur_line)))
	{

	}

	if (!ft_strcmp("##start", cur_line))
	{
		ft_printf("start :<%s>\n", cur_line);
		
	}
	else if (!ft_strcmp("##end", cur_line))
	{
		ft_printf("end :<%s>\n", cur_line);
		
	}
	else if (ft_strstr(cur_line, "#"))
		ft_printf("a comment :<%s>\n", cur_line);
	else if (ft_strstr(cur_line, " "))//room
		ft_printf("a room %s\n", cur_line);
	else if (!ft_strstr(cur_line, " "))
		ft_printf("a link :<%s>\n", cur_line);
	else if (!first && ft_isdigit(ft_atoi(cur_line)))
	{
		ft_printf("begins with int :<%s>\n", cur_line);
		first = 1;
	}
	else
	{
		ft_printf("ERROR <%s>\n", cur_line);
		return (0);
	}
	return (1);
}*/


int is_num(const char *str)
{
	int i = 0;

	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

int is_room(const char *line)
{
	//roomn N N\n
	if (!line)
		return (0);
	char **p = ft_strsplit(line, ' ');//dont forget to free
	//check for \n
	if (ft_wtlen(p) == 3)
	{
		if (ft_strlen(p[0]) > 0 && is_num(p[1]) && is_num(p[2]))
		{
			ft_printf("is room %s\n", line);
			return (1);
		}
	}
	return (0);
}

int is_link(const char *line)
{
	//link N-N\n
	if (!line)
		return (1);
	if (ft_strstr(line, " "))
		return (0);
	char **p = ft_strsplit(line, '-');//tofree
	if (ft_wtlen(p) == 2)
	{
		if (ft_strlen(p[0]) > 0 && ft_strlen(p[1]) > 0 && ft_strcmp(p[0], p[1]) != 0)
		{
			ft_printf("is link %s\n", line);
			return (0);
		}
	}
	return (1);
}

int is_first_line(const char *line)
{
	if (is_num(line))
		ft_printf("1ST LINE IS NUM :<%s>\n", line);
	return (is_num(line));
}

int is_comment(const char *line)
{
	if (!line)
		return (1);
	if (line[0] == '#' && ft_strcmp("##start", line) != 0 && ft_strcmp("##end", line) != 0)
	{
		ft_printf("COMMENT :<%s>\n", line);
		return (0);
	}
	return (1);
}

int is_start_end(const char *line)
{
	static int bstart;
	static int bend;

	if (!line)
		return (0);
	if (!ft_strcmp("##start", line) && bstart == 0)
	{
		ft_printf("start :<%s>\n", line);
		bstart = 0;
	}
	else if (!ft_strcmp("##end", line) && bend == 0)
	{
		ft_printf("end :<%s>\n", line);
		bend = 0;
	}
	else if (!ft_strcmp("##start", line) || !ft_strcmp("##end", line))
	{
		ft_printf("ERROR double start/end %s\n", line);
		return (0);
		
	}
	return(1);
}

int check_line(const char *line)
{
	if (!line)
		return (0);
	if (ft_strlen(line) > 0 && line[0] == 'L')
		return (0);
	
	//int (*fun_ptr)(const char *) = &is_room;
	is_first_line(line);
	is_room(line);
	is_link(line);
	is_comment(line);
	is_start_end(line);
	
	return (0);
}

int is_room_end_start(const char *line)
{
	if (!is_start_end(line))
		return (0);
	if (!is_room(line))
		return (0);
	return (1);
}
/*
int is_end(const char *line, int fd)
{
	char *tmp;

	if (!line)
		return (0);
	if (ft_strlen(line) == 0 && !get_next_line(fd, tmp))
		return ();
	return ();

}
*/
int	lemin_parser(t_lemindata *lda)
{
	//int fd = open("/Users/trponess/Documents/lemin_c/maps/invalid_maps/more_max_int", O_RDONLY);
	int fd = open("/Users/trponess/Documents/lemin_c/maps/maps/easy", O_RDONLY);
	char *line = NULL;
	int r = 0;

	 int (*check_fun[3])(const char *) =
	 {
		&is_first_line,
		&is_room_end_start,
		&is_link,
	 };
	int fun_i = 0;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		if (fun_i == 0 && !check_fun[fun_i](line))
		{
			ft_printf("ERRRROOOOR, leaving parser on FUN %d\n\n", fun_i);
			return (1);
		}
		else if (!is_comment(line) && !check_fun[fun_i](line))
		{
			++fun_i;
			if (fun_i > 2)
			{
				ft_printf("ERRRROOOOR, leaving parser on FUN %d\n\n", fun_i);
				return (1);
			}			
			if (!check_fun[fun_i](line))
			{
				ft_printf("ERRRROOOOR, leaving parser on FUN %d\n\n", fun_i);
				return (1);
			}
		}
		if (fun_i == 0)
			++fun_i;
		
		//ft_printf("ERRRROOOOR, leaving parser on FUN %d\n\n", fun_i);

		t_list *ptr = ft_lst_push_back(&(lda->map), NULL, 0);
		ptr->content = line;
		/*
		ft_printf("line :<%s>\n", line);
		ft_printf("ptr->content:<%s>\n", (char *)ptr->content);
		*/
	}
	/*
	ft_lst_at(lda->map, 2)->content = "5";
	ft_printf("2 ptr->content:<%s>\n", (char *)ft_lst_at(lda->map, 2)->content);
	ft_printf("0 ptr->content:<%s>\n", (char *)ft_lst_at(lda->map, 0)->content);
	*/
	//if (lda->options & O_ANTS)
	
	ft_printf("\nHELLO, I COMPILED!!!!!\n");
	return (0);
}
