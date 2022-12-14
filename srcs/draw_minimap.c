/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:37:56 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/22 18:14:48 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_data *a, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < a->map.size)
	{
		j = 0;
		while (j++ < a->map.size)
			put_pixel(&a->mini, x + j - 1, y + i, 0x808080);
		i++;
	}
	i = 1;
	while (i < a->map.size - a->map.border)
	{
		j = a->map.border;
		while (j++ < a->map.size - a->map.border)
			put_pixel(&a->mini, x + j - 1, y + i, color);
		i++;
	}
}

void	draw_cam(t_data *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < a->cam.size)
	{
		j = 0;
		while (j++ < a->cam.size)
			put_pixel(&a->mini, j - 1 + a->cam.x / BSIZE * a->map.size,
				i + a->cam.y / BSIZE * a->map.size, a->cam.color);
		i++;
	}
	i = 0;
	while (i < a->cam.size - 2)
	{
		j = 0;
		while (j < a->cam.size - 2)
		{
			put_pixel(&a->mini, j + a->cam.x / BSIZE * a->map.size + a->cam.dx * 5,
				i + a->cam.y / BSIZE * a->map.size + a->cam.dy * 5, a->cam.color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *a)
{
	int	i;
	int	j;

	i = 0;
	while (a->map.map[i] != NULL)
	{
		j = 0;
		while (a->map.map[i][j] != '\0')
		{
			if (a->map.map[i][j] == '1')
				draw_tile(a, j * a->map.size, i * a->map.size, 0x22FFFFFF);
			if (a->map.map[i][j] == 'C')
				draw_tile(a, j * a->map.size, i * a->map.size, 0xFF0000);
			if (a->map.map[i][j] == '0' || a->map.map[i][j] == 'O')
				draw_tile(a, j * a->map.size, i * a->map.size, 0x99000000);
			j++;
		}
		i++;
	}
	draw_cam(a);
}

void	draw_point(t_data *a, int x, int y)
{
	put_pixel(&a->mini, x / BSIZE * a->map.size, y / BSIZE * a->map.size, 0xFF0000);
	put_pixel(&a->mini, x / BSIZE * a->map.size + 1, y / BSIZE * a->map.size, 0xFF0000);
	put_pixel(&a->mini, x / BSIZE * a->map.size, y / BSIZE * a->map.size + 1, 0xFF0000);
	put_pixel(&a->mini, x / BSIZE * a->map.size + 1, y / BSIZE * a->map.size + 1, 0xFF0000);
}
