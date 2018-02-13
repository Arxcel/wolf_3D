/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:18:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/13 18:18:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wolf.h"

static void			ft_read_line(int *m, char *l, int m_w)
{
	char	**buf;
	int		i;

	i = -1;
	buf = ft_strsplit(l, ' ');
	while (buf[++i])
	{
		if (i > m_w)
			MSG("Error in map parameters. Width.");
		m[i] = ft_atoi(buf[i]);
		free(buf[i]);
	}
	free(buf);
	if (i != m_w)
		MSG("Error in map parameters. Width.");
}

static void			ft_read_map(int fd, t_map *map)
{
	int		ret;
	char	*l;
	int		h;

	h = 0;
	while ((ret = get_next_line(fd, &l)))
	{
		if (ret == -1)
			MSG("Error in reading file.");
		ft_read_line(map->w_map[h], l, map->m_w);
		free(l);
		if (h > map->m_h)
			MSG("Wrong map parameters.");
		h++;
	}
	if (h != map->m_h)
		MSG("Error in map parameters. Height.");
}

static void			ft_get_map_params(int fd, t_map *map)
{
	int		i;
	char	*l;
	char	**buf;
	short	err;

	i = -1;
	err = 0;
	while (++i < 2)
	{
		if (get_next_line(fd, &l) < 0)
			MSG("Error reading the file.");
		buf = ft_strsplit(l, ' ');
		free(l);
		if (!ft_strcmp("WIDTH", buf[0]))
			buf[1] && ft_atoi(buf[1]) > 0 ? map->m_w = ft_atoi(buf[1]) : err++;
		else if (!ft_strcmp("HEIGHT", buf[0]))
			buf[1] && ft_atoi(buf[1]) > 0 ? map->m_h = ft_atoi(buf[1]) : err++;
		else
			err++;
		free(buf[0]);
		free(buf[1]);
		free(buf);
	}
	if (err > 0 || map->m_h < 10 || map->m_w < 10)
		MSG("Wrong map parameters.");
}

void				ft_ftoa(const char *file, t_map *map)
{
	int		fd;
	int		i;

	i = -1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		MSG("Error opening the file.");
	ft_get_map_params(fd, map);
	if (!(map->w_map = (int**)malloc(sizeof(int*) * map->m_h)))
		MSG("Error allocating memory.");
	while (++i < map->m_h)
		if (!(map->w_map[i] = (int*)malloc(sizeof(int) * map->m_w)))
			MSG("Error allocating memory.");
	ft_read_map(fd, map);
	if (close(fd) < 0)
		MSG("Error closing the file.");
}
