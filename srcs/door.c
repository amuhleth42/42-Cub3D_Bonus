/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 01:23:58 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/22 01:41:26 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_door(t_data *a, int x, int y)
{
	int	mx;
	int	my;

	mx = ((int)x) >> 6;
	my = ((int)y) >> 6;
	if (0 <= mx && mx < a->map.x && 0 <= my && my < a->map.y
		&& a->map.map[my][mx] == 'C')
	{
		ft_printf("ayyyya\n");
		a->map.map[my][mx] = 'O';
		return (1);
	}
	else if (0 <= mx && mx < a->map.x && 0 <= my && my < a->map.y
		&& a->map.map[my][mx] == 'O')
	{
		ft_printf("ayyyya\n");
		a->map.map[my][mx] = 'C';
		return (1);
	}
	return (0);
}

void	open_door(t_data *a)
{
	if (check_door(a, a->cam.x + 64, a->cam.y))
		return ;
	if (check_door(a, a->cam.x - 64, a->cam.y))
		return ;
	if (check_door(a, a->cam.x, a->cam.y + 64))
		return ;
	if (check_door(a, a->cam.x, a->cam.y - 64))
		return ;
}
