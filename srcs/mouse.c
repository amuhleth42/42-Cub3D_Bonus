/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:45:32 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/16 16:55:47 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_data *a)
{
	a->mouse.lastx = a->mouse.x;
	a->mouse.lasty = a->mouse.y;
	a->mouse.x = x;
	a->mouse.y = y;
	a->mouse.dx = a->mouse.x - a->mouse.lastx;
	a->mouse.dy = a->mouse.y - a->mouse.lasty;
	//if (dx)
	//	rotate(a, dx * 0.004);
	return (0);
}
