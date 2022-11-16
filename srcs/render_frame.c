/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:03:53 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/16 16:57:21 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_timestamp(t_data *a)
{
	double			sec;
	double			usec;

	gettimeofday(&a->frame, NULL);
	sec = a->frame.tv_sec - a->start.tv_sec;
	usec = a->frame.tv_usec - a->start.tv_usec;
	return (sec * 1000 + usec / 1000);
}

int	get_time_diff(struct timeval *last, struct timeval *now)
{
	double	sec;
	double	usec;

	sec = now->tv_sec - last->tv_sec;
	usec = now->tv_usec - last->tv_usec;
	return (sec * 1000 + usec / 1000);
}

void	clear_img(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->y)
	{
		j = 0;
		while (j++ < img->x)
			put_pixel(img, j, i, 0x0);
		i++;
	}
}

void	render_frame(t_data *a)
{
	//int	diff;
	raycasting(a);
	mlx_put_image_to_window(a->mlx, a->win, a->fp.img, 0, 0);
	if (a->keys.m)
	{
		draw_map(a);
		mlx_put_image_to_window(a->mlx, a->win, a->mini.img, 50, 50);
	}
	draw_ui(a);
	a->last_frame = a->frame;
	a->diff = get_time_diff(&a->last_frame, &a->frame);
	while (a->diff < 15)
	{
		usleep(500);
		get_timestamp(a);
		a->diff = get_time_diff(&a->last_frame, &a->frame);
	}
	//ft_printf("Time: %d, ", get_timestamp(a));
	//ft_printf("fps: %d\n", 1000 / get_time_diff(&a->last_frame, &a->frame));
}

int	loop_render(t_data *a)
{
	if (a->keys.w)
		move(a, 1);
	if (a->keys.s)
		move(a, -1);
	if (a->keys.a)
		rl_move(a, -1);
	if (a->keys.d)
		rl_move(a, 1);
	if (a->keys.left)
		rotate(a, -0.04);
	if (a->keys.right)
		rotate(a, 0.04);
	if (a->mouse.dx)
	{
		rotate(a, a->mouse.dx * 0.004);
		a->mouse.dx = 0;
	}
	render_frame(a);
	return (0);
}
