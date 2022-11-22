/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:37:54 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/21 22:53:38 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	manage_args(t_data *a, int ac, char **av)
{
	if (ac != 2)
		quit(a, "Please enter a map as an argument !");
	if (!av[1])
		quit(a, "Error: argument is NULL");
	return (0);
}

void	print_right_line(char *line, int x)
{
	int	i;

	i = -1;
	if (x != 0)
	{
		while (++i <= (int)ft_strlen(line))
		{
			printf("%c", line[i]);
			if (i == x)
				printf("%s'%c' => '%c'%s ", COL_RED, line[i - 1],
					line[i], COL_RES);
		}
		printf("\n");
	}
	else
	{
		while (++i <= (int)ft_strlen(line))
		{
			if (i == x)
				printf("%s'%c' <= '%c'%s", COL_RED, line[i - 1],
					line[i], COL_RES);
			printf("%c", line[i]);
		}
		printf("\n");
	}
}

int	manage_map_error(char *line, int y, int x, int err)
{
	printf("\n%sThere is an error on line:	%d%s\n\n", COL_RED, y, COL_RES);
	if (err == 1)
		print_right_line(line, x);
	if (err == 2)
		print_right_line(line, x);
	if (err == 3)
		print_right_line(line, x);
	return (1);
}
