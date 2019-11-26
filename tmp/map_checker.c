/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 08:58:47 by trponess          #+#    #+#             */
/*   Updated: 2019/11/26 14:37:36 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lemindata.h"
#include "lemin_options.h"

void ft_error(char *msg ,const char *line, int r)
{
	ft_dprintf(2,"ERROR > \nmsg:%s \nline:|%s| \ngnl:%d", msg,line,r);
	ft_exit(NULL, 1);
}

int is_num(const char *str)
{
	int i = 0;

	if (!str)
		return (0);
	if (str[0] == '-' || str[0] != '+')
		++i;
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
	if (ft_wtlen(p) == 3)
	{
		if (ft_strlen(p[0]) > 0 && is_num(p[1]) && is_num(p[2]))
		{
			ft_printf("IS ROOM <%s>\n", line);
			return (1);
		}
	}
	return (0);
}

int is_link(const char *line)
{
	//link N-N\n
	if (!line)
		return (0);
	if (ft_strstr(line, " "))
		return (0);
	char **p = ft_strsplit(line, '-');//tofree
	if (ft_wtlen(p) == 2)
	{
		if (ft_strlen(p[0]) > 0 && ft_strlen(p[1]) > 0 && ft_strcmp(p[0], p[1]) != 0)
		{
			ft_printf("IS LINK <%s>\n", line);
			return (1);
		}
	}
	return (0);
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
	if (line[0] == '#') //&& ft_strcmp("##start", line) != 0 && ft_strcmp("##end", line) != 0)
	{
		ft_printf("(comment) :<%s>\n", line);
		return (1);
	}
	return (0);
}


int check_empty_start_L(const char *line)
{
	if (!line)
		return (0);
	if (ft_strlen(line) > 0 && line[0] == 'L')
		return (0);
	return (1);
}

/* DOESNT WORK

int is_room_end_start(const char *line)
{
	if (!is_start_end(line))
		return (0);
	if (line[0] != '#' && !is_room(line))
		return (0);
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
		ft_error("double start/end", line, -2);
		return (0);		
	}
	return(1);
}
*/

int	lemin_parser(t_lemindata *lda)
{	
	char *line = NULL;
	int r = 0;
	int (*check_fun[2])(const char *) =
	{
		&is_room,
		&is_link
	};
	int fun_i = 0;   

	if ((r = get_next_line(0, &line)) > 0)
	{
		if (!is_first_line(line))
			ft_error("DONT begins with int LINE",line, r);
	}
	else
		ft_error("gnl STOPPED READING or empty file GNL value", line, r);
	
	t_list *ptr = ft_lst_push_back(&(lda->map), NULL, 0);
	ptr->content = line;
	while ((r = get_next_line(0, &line)) > 0)
	{
		if (!check_empty_start_L(line))//if last empty line , gnl stopped alreayd correct , otherwise file contains emprty line
			ft_error("start with L or empty line : ", line, r);
		if (!is_comment(line) && !check_fun[fun_i](line))
		{
			++fun_i;
			if (fun_i > 1 || !check_fun[fun_i](line))//CHECK LINK if room fails
				ft_error("not LINK/ROOM/COMMENT: ", line, r);
			else 
				lda->nb_links++;
		}
		else 
		{
			if (fun_i == 0 && line[0] != '#')
				lda->nb_rooms++;
			if (fun_i == 1 && line[0] != '#')
				lda->nb_links++;
		}
		t_list *ptr = ft_lst_push_back(&(lda->map), NULL, 0);
		ptr->content = line;
	}
	if (r == -1)
		ft_error("ERROR gnl broke: LINE= ", line, r);
	if (fun_i != 1)
		ft_error("ERROR file dont finish with links LINE:", line, r);
	return (0);
}


//check double startend
//