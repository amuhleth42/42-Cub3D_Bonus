/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 01:23:58 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/22 16:56:06 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_door(t_data *a, int x, int y)
{
	int	mx;
	int	my;

	mx = ((int)x) >> 6;
	my = ((int)y) >> 6;
	printf("mx:%d, my:%d\n", mx, my);
	if (0 <= mx && mx < a->map.x && 0 <= my && my < a->map.y
		&& a->map.map[my][mx] == 'C')
	{
		printf("hayyya\n");
		a->map.map[my][mx] = 'O';
		return (1);
	}
	else if (0 <= mx && mx < a->map.x && 0 <= my && my < a->map.y
		&& a->map.map[my][mx] == 'O')
	{
		printf("hayyya\n");
		a->map.map[my][mx] = 'C';
		return (1);
	}
	return (0);
}

void	open_door(t_data *a)
{
	int	x;
	int	y;

	x = a->cam.x + a->cam.dx * 64;
	y = a->cam.y + a->cam.dy * 64;

	if (check_door(a, x, y))
		return ;
}
