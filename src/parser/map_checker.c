/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trponess <trponess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 08:58:47 by trponess          #+#    #+#             */
/*   Updated: 2019/12/03 10:37:08 by trponess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lemindata.h"
#include "lemin_options.h"

int		is_int_num(const char *str)
{
	long long int	nb;
	int				i;

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

int		is_room(const char *line)
{
	size_t	i;
	char	**p;
	int		nb_space;
	int		ret;

	ret = 0;
	i = 0;
	nb_space = 0;
	p = ft_strsplit(line, ' ');
	while (i < ft_strlen(line))
	{
		if (line[i] == ' ')
			++nb_space;
		++i;
	}
	if (nb_space == 2 && ft_wtlen(p) == 3)
		if (ft_strlen(p[0]) > 0 && !ft_strstr(p[0], "-") && is_int_num(p[1]) \
		&& is_int_num(p[2]))
			ret = 1;
	ft_wtfree(p);
	return (ret);
}

int		is_link(const char *line)
{
	int		i;
	char	**p;
	int		ret;

	ret = 0;
	i = 0;
	if (!line || ft_strstr(line, " "))
		return (ret);
	p = ft_strsplit(line, '-');
	if (p && ft_wtlen(p) == 2)
		if (ft_strlen(p[0]) > 0 && ft_strlen(p[1]) > 0 && p[0][0] != '#')
			ret = 1;
	ft_wtfree(p);
	return (ret);
}

int		is_comment(const char *line)
{
	if (!line)
		return (1);
	if (line[0] == '#')
		return (1);
	return (0);
}

int		map_checker(t_lemindata *lda)
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
		check_empty_start_l_space(line, r);
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
	return (0);
}
