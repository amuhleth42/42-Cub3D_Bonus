/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:39:30 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/22 16:17:54 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	cast_ray(t_data *a, float ra, int i)
{
	t_ray	h;
	t_ray	v;

	ft_bzero(&h, sizeof(h));
	ft_bzero(&v, sizeof(v));
	h.h = 1;
	horizontal_check(a, &h, ra);
	vertical_check(a, &v, ra);
	if (h.dist < v.dist)
	{
		h.i = i;
		if (ra < PI)
			render_column(a, &h, &a->s, 1);
		else
			render_column(a, &h, &a->n, 0);
	}
	else
	{
		v.i = i;
		if (PI / 2 < ra && ra < 3 * PI / 2)
			render_column(a, &v, &a->w, 1);
		else
			render_column(a, &v, &a->e, 0);
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
