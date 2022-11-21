/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:39:30 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/21 23:40:10 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	cast_ray(t_data *a, float ra, int i)
{
	t_ray	r;

	ft_bzero(&r, sizeof(r));
	horizontal_check(a, &r, ra);
	vertical_check(a, &r, ra);
	r.i = i;
	if (r.hdist < r.vdist)
	{
		r.dist = r.hdist;
		r.value = r.hx;
		if (ra < PI)
			render_column(a, &r, &a->s, 1);
		else
			render_column(a, &r, &a->n, 0);
	}
	else
	{
		r.dist = r.vdist;
		r.value = r.vy;
		if (PI / 2 < ra && ra < 3 * PI / 2)
			render_column(a, &r, &a->w, 1);
		else
			render_column(a, &r, &a->e, 0);
	}
}

void	*thread_routine(void *arg)
{
	t_data		*a;
	t_thread	*t;
	float		start_angle;
	int			i;

	t = arg;
	a = t->backup;
	start_angle = add_rad(a->cam.a, -(VIEW_FIELD / 2));
	t->nb_column = WIN_WIDTH / COLUMN_SIZE;
	t->slice_size = t->nb_column / NB_THREAD;
	t->this_slice = t->slice_size;
	if (t->nb == NB_THREAD - 1)
		t->this_slice += t->nb_column % NB_THREAD;
	t->slice_a = VIEW_FIELD / NB_THREAD;
	start_angle = add_rad(start_angle, t->slice_a * t->nb);
	i = 0;
	while (i < t->this_slice)
	{
		cast_ray(a, add_rad(start_angle, i * VIEW_FIELD / t->nb_column),
			t->slice_size * t->nb + i);
		i++;
	}
	return (NULL);
}

void	raycasting(t_data *a)
{
	int		i;

	i = 0;
	while (i < NB_THREAD)
	{
		a->thread[i].backup = a;
		a->thread[i].nb = i;
		pthread_create(&a->thread[i].tid, NULL, &thread_routine, a->thread + i);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_join(a->thread[i].tid, NULL);
		i++;
	}
}
