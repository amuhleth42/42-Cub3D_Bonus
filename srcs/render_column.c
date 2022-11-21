/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_column.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:03:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/21 14:27:53 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	fix_fisheye(float dist, int i)
{
	float	angle;

	angle = add_rad(-PI / 5, i * VIEW_FIELD / (WIN_WIDTH / COLUMN_SIZE));
	return (dist * cos(angle));
}

void	set_column_data(t_data *a, t_img *img, t_ray *r, int invert)
{
	r->dist = fix_fisheye(r->dist, r->i);
	r->size = 64 * WIN_WIDTH / r->dist;
	r->step = img->y / r->size;
	r->tyoff = 0;
	r->offset = WIN_HEIGHT / 2 - r->size / 2 - (a->mouse.y - WIN_HEIGHT / 2);
	r->ty = r->step * r->tyoff;
	r->tx = (int)(r->value / (64 / img->x)) % img->x;
	if (invert)
		r->tx = img->x - 1 - r->tx;
}

void	render_column(t_data *a, t_ray *r, t_img *img, int invert)
{
	set_column_data(a, img, r, invert);
	draw_ceiling(a, r, r->i);
	draw_column(a, r, r->i, img);
	draw_floor(a, r, r->i);
}
