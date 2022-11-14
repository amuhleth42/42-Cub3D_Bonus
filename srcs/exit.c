/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:38:12 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/14 15:15:55 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_data *a)
{
	/*int	i;

	i = 0;
	while (a->map.map[i] != NULL)
	{
		if (a->map.map[i] != NULL)
			free(a->map.map[i]);
		a->map.map[i] = NULL;
		i++;
	}*/
	if (a->map.map != NULL)
		free(a->map.map);
}

void	exit_all(t_data *a)
{
	free_map(a);
	mlx_destroy_image(a->mlx, a->mini.img);
	mlx_destroy_image(a->mlx, a->fp.img);
	exit(EXIT_SUCCESS);
}

int	red_cross(t_data *a)
{
	(void)a;
	exit(0);
	return (0);
}
