/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:44:46 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/16 16:35:52 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ui(t_data *a)
{
	char	*fps;

	fps = ft_itoa(1000 / a->diff);
	mlx_string_put(a->mlx, a->win, WIN_WIDTH - 150, 50, 0xFFFFFF, "FPS: ");
	mlx_string_put(a->mlx, a->win, WIN_WIDTH - 100, 50, 0xFFFFFF, fps);
	if (fps)
		free(fps);
}
