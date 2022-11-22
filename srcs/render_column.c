/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_column.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:03:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/22 18:27:08 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

float	fix_fisheye(float dist, int i)
{
	float	angle;

	angle = add_rad(-(VIEW_FIELD / 2), i * VIEW_FIELD / (WIN_WIDTH / COLUMN_SIZE));
	return (dist * cos(angle));
}

void	set_column_data(t_data *a, t_img *img, t_ray *r, int invert)
{
	r->dist = fix_fisheye(r->dist, r->i);
	r->size = BSIZE * WIN_WIDTH / r->dist;
	r->step = img->y / r->size;
	r->tyoff = 0;
	r->offset = WIN_HEIGHT / 2 - r->size / 2 - (a->mouse.y - WIN_HEIGHT / 2);
	r->ty = r->step * r->tyoff;
	r->tx = (long long)(r->value / (BSIZE / img->x)) % (long long)img->x;
	//r->tx = r->value / (BSIZE / img->x) % (float)img->x;
	printf("res:%lld\n", (long long)(r->value / (BSIZE / img->x)));
	printf("tx:%f\n", r->tx);
	if (invert)
		r->tx = img->x - 1 - r->tx;
}

void	render_column(t_data *a, t_ray *r, t_img *img, int invert)
{
	if (r->door)
		img = &a->d;
	set_column_data(a, img, r, invert);
	draw_ceiling(a, r, r->i);
	draw_column(a, r, r->i, img);
	draw_floor(a, r, r->i);
}
