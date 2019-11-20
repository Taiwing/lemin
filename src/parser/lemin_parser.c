/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 08:58:47 by trponess          #+#    #+#             */
/*   Updated: 2019/11/20 14:36:47 by trponess         ###   ########.fr       */
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
	//check for \n
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
	if (line[0] == '#' && ft_strcmp("##start", line) != 0 && ft_strcmp("##end", line) != 0)
	{
		ft_printf("(comment) :<%s>\n", line);
		return (1);
	}
	return (0);
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

int check_empty_start_L(const char *line)
{
	if (!line)
		return (0);
	if (ft_strlen(line) > 0 && line[0] == 'L')
		return (0);
	return (1);
}

int is_room_end_start(const char *line)
{
	if (!is_start_end(line))
	{
		//ft_printf("stratend error\n");
		return (0);
	}
	if (line[0] != '#' && !is_room(line))
	{
		//ft_printf("room error\n");
		return (0);
	}
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

#include <dirent.h> 
#include <stdio.h> 

void list_files(char *path) 
{
  DIR *d;
  struct dirent *dir;
  //d = opendir("/Users/trponess/Documents/lemin_c/maps/maps");
  d = opendir(path);
  ft_printf("d:%d\n", d);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
}

int	lemin_parser(t_lemindata *lda, char *path)
{
	//CHECK HOW OPTIONS TAKE IN FILE FOR < AND ARGV1	
	//PATH IS ONE MAP A FILE 
	//CHECK FILE NAME IF FILE AND IF OPENS
	if (path == NULL)
		ft_exit(ft_strjoin("ERROR path == NULL:", path), 1);

	//int fd = open("/Users/trponess/Documents/lemin_c/maps/invalid_maps/more_max_int", O_RDONLY);
	int fd = open(path, O_RDONLY);
	char *line = NULL;
	int r = 0;

	 int (*check_fun[2])(const char *) =
	 {
		&is_room_end_start,
		&is_link
	 };
	int fun_i = 0;

	//firsline
	if ((r = get_next_line(fd, &line)) > 0)
	{
		if (!is_first_line(line))
			ft_exit(ft_strjoin("DONT begins with int LINE:", line), 1);
	}
	else
		ft_exit(ft_strjoin("gnl STOPPED READING or empty file GNL value r=:",line), 1);
	
	 //check if stuff is missing
	t_list *ptr = ft_lst_push_back(&(lda->map), NULL, 0);
	ptr->content = line;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		if (!check_empty_start_L(line))//if last empty line , gnl stopped alreayd correct , otherwise file contains emprty line
			ft_exit(ft_strjoin("ERROR start with L or empty line : ", line), 1);
		if (!is_comment(line) && !check_fun[fun_i](line))
		{
			++fun_i;	
			if (fun_i > 1 || !check_fun[fun_i](line))//CHECK LINK if room fails
			{
				ft_exit(ft_strjoin("ERROR not LINK/ROOM/COMMENT: ", line), 1);
			}
		}
		
		//ft_printf("ERRRROOOOR, leaving parser on FUN %d\n\n", fun_i);

		t_list *ptr = ft_lst_push_back(&(lda->map), NULL, 0);
		ptr->content = line;
		/*
		ft_printf("line :<%s>\n", line);
		ft_printf("ptr->content:<%s>\n", (char *)ptr->content);
		*/
	}
	if (r == -1)
		ft_exit(ft_strjoin("ERROR gnl broke: LINE= ", line), 1);
	if (fun_i != 1)
		ft_exit(ft_strjoin("ERROR file dont finish with links LINE:", line), 1);

	//CHECK IF GNL STOPS IF NO START OR END , FALSE
	/*
	ft_lst_at(lda->map, 2)->content = "5";
	ft_printf("2 ptr->content:<%s>\n", (char *)ft_lst_at(lda->map, 2)->content);
	ft_printf("0 ptr->content:<%s>\n", (char *)ft_lst_at(lda->map, 0)->content);
	*/
	//if (lda->options & O_ANTS)
	
	//list_files("/Users/trponess/Documents/lemin_c/maps/invalid_maps");
	return (0);
}
