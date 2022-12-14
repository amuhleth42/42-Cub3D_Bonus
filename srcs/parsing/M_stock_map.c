/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdi-noce <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:17:58 by kdi-noce          #+#    #+#             */
/*   Updated: 2022/11/22 18:08:48 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	reset_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			map->map[y][x] = ' ';
			++x;
		}
		++y;
	}
}

int	create_map(t_map *map)
{
	int		i;

	map->map = ft_calloc(sizeof(char *), map->y + 1);
	if (map->map == NULL)
		return (1);
	map->map[map->y] = NULL;
	i = 0;
	while (i < map->y)
	{
		map->map[i] = ft_calloc(sizeof(char), map->x + 1);
		if (map->map[i] == NULL)
		{
			while (i--)
				free(map->map[i]);
			free(map->map);
			return (1);
		}
		map->map[i][map->x] = '\0';
		++i;
	}
	reset_map(map);
	return (0);
}

int	parse_player(char c, int y, int x, t_cam *cam)
{
	if (!ft_strchr("NSWE", c))
		return (1);
	cam->x = (x + 0.5) * BSIZE;
	cam->y = (y + 0.5) * BSIZE;
	if (c == 'E')
		cam->a = 0;
	else if (c == 'S')
		cam->a = PI / 2.0;
	else if (c == 'W')
		cam->a = PI;
	else if (c == 'N')
		cam->a = 3 * PI / 2.0;
	return (0);
}

int	fill_map(char **lines, t_map *map, t_cam *cam)
{
	int	player_found;

	player_found = 0;
	map->y = -1;
	while (lines[++map->y])
	{
		map->x = -1;
		printf("%s\n", lines[map->y]);
		while (lines[map->y][++map->x])
		{
			if (lines[map->y][map->x] == '0' || lines[map->y][map->x] == '1'
				|| lines[map->y][map->x] == 'C')
				map->map[map->y][map->x] = lines[map->y][map->x];
			else if (ft_isalpha(lines[map->y][map->x]))
			{
				if (parse_player(lines[map->y][map->x], map->y, map->x, cam))
					return (manage_map_error(lines[map->y],
							map->y + 1, map->x, 1));
				++player_found;
				map->map[map->y][map->x] = '0';
			}
		}
	}
	return (player_found != 1);
}
