/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:45:32 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/16 20:04:50 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(t_data *a)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(a->win, &x, &y);
	a->mouse.lastx = WIN_WIDTH / 2;
	//a->mouse.lasty = a->mouse.y;
	a->mouse.x = x;
	a->mouse.y = y;
	a->mouse.dx = a->mouse.x - a->mouse.lastx;
	//a->mouse.dy = a->mouse.y - a->mouse.lasty;
	mlx_mouse_move(a->win, WIN_WIDTH / 2, a->mouse.y);
	return (0);
}
