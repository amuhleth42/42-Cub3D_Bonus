/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:36:13 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/22 18:11:52 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_horizontal_start(t_data *a, t_ray *r, float ra)
{
	if (ra > PI)
	{
		r->y = (((int)a->cam.y >> SHIFT) << SHIFT) - 0.01;
		r->x = (a->cam.y - r->y) * (-1 / tan(ra)) + a->cam.x;
		r->yoff = -BSIZE;
		r->xoff = -r->yoff * (-1 / tan(ra));
	}
	else if (ra < PI)
	{
		r->y = (((int)a->cam.y >> SHIFT) << SHIFT) + BSIZE;
		r->x = (a->cam.y - r->y) * (-1 / tan(ra)) + a->cam.x;
		r->yoff = BSIZE;
		r->xoff = -r->yoff * (-1 / tan(ra));
	}
	else
	{
		r->x = a->cam.x;
		r->y = a->cam.y;
	}
}

void	set_vertical_start(t_data *a, t_ray *r, float ra)
{
	if (PI / 2 < ra && ra < 3 * PI / 2)
	{
		r->x = (((int)a->cam.x >> SHIFT) << SHIFT) - 0.01;
		r->y = (a->cam.x - r->x) * -tan(ra) + a->cam.y;
		r->xoff = -BSIZE;
		r->yoff = -r->xoff * -tan(ra);
	}
	else if (3 * PI / 2 < ra || ra < PI / 2)
	{
		r->x = (((int)a->cam.x >> SHIFT) << SHIFT) + BSIZE;
		r->y = (a->cam.x - r->x) * -tan(ra) + a->cam.y;
		r->xoff = BSIZE;
		r->yoff = -r->xoff * -tan(ra);
	}
	else
	{
		r->x = a->cam.x;
		r->y = a->cam.y;
	}
}

int	hit_door(t_data *a, t_ray *r)
{
	int	x;
	int	y;

	x = ((int)r->x) >> SHIFT;
	y = ((int)r->y) >> SHIFT;
	if (0 <= x && x < a->map.x && 0 <= y && y < a->map.y
		&& a->map.map[y][x] == 'C')
	{
		r->door = 1;
		r->x += r->xoff / 2.0;
		r->y += r->yoff / 2.0;
		return (1);
	}
	return (0);
}

int	hit_wall(t_data *a, t_ray *r)
{
	int	x;
	int	y;

	x = ((int)r->x) >> SHIFT;
	y = ((int)r->y) >> SHIFT;
	if (0 <= x && x < a->map.x && 0 <= y && y < a->map.y
		&& a->map.map[y][x] == '1')
		return (1);
	return (0);
}

void	horizontal_check(t_data *a, t_ray *r, float ra)
{
	int	i;

	r->ra = ra;
	set_horizontal_start(a, r, ra);
	i = 0;
	while (i < a->map.y)
	{
		if (hit_door(a, r))
			break ;
		if (hit_wall(a, r))
			break ;
		r->x += r->xoff;
		r->y += r->yoff;
		i++;
	}
	r->dist = dist(a->cam.x, a->cam.y, r->x, r->y);
	r->value = r->x;
}

void	vertical_check(t_data *a, t_ray *r, float ra)
{
	int	i;

	r->ra = ra;
	set_vertical_start(a, r, ra);
	i = 0;
	while (i < a->map.x)
	{
		if (hit_door(a, r))
			break ;
		if (hit_wall(a, r))
			break ;
		r->x += r->xoff;
		r->y += r->yoff;
		i++;
	}
	r->dist = dist(a->cam.x, a->cam.y, r->x, r->y);
	r->value = r->y;
}
