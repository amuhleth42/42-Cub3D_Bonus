/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdi-noce <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:05:31 by kdi-noce          #+#    #+#             */
/*   Updated: 2022/11/22 14:06:34 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_the_rest_color(char *input)
{
	char	**new_array;
	int		args;
	int 	i;

	args = 0;
	i = -1;
	new_array = ft_split(input, ',');
	while (new_array[args])
		args++;
	while (new_array[++i])
		free(new_array[i]);
	return (args);
}

int	check_color(char *array, t_text *dirct, t_color *color)
{
	int		i;
	char	*tmp_color;

	i = 0;
	tmp_color = check_space(array, 1);
	if (!ft_isalpha(array[i]) && array[i])
		array = check_space(array, 0);
	if (!dirct->f || !dirct->c)
	{
		if (!array || !tmp_color)
			return (0);
		if ((array[0] != 'F' && array[0] != 'C') && !ft_isalnum(array[1]))
			return (0);
	}
	if (!ft_strncmp(array, "F", 1))
		manage_path_dirct_c(color, dirct, tmp_color, 1);
	else if (!ft_strncmp(array, "C", 1))
		manage_path_dirct_c(color, dirct, tmp_color, 2);
	if (dirct->f == 1 && dirct->c == 1)
		return (2);
//	free(array)
	return (0);
}

int	get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	set_color(t_data *a, t_color *color)
{
	char	**tab;

	tab = ft_split(color->c, ',');
	a->map.ceiling = get_color(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]));
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	tab = ft_split(color->f, ',');
	a->map.floor = get_color(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]));
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
}

int	parse_colors(t_data *a, t_args *input)
{
	int		idx_color;
	t_text	dirct;
	t_color	color;

	(void)a;
	input->y = 0;
	idx_color = 0;
	struct_init(&dirct);
	while (input->input[input->y] && input->input[input->y][0])
	{
		idx_color = check_color(input->input[input->y], &dirct, &color);
		if (idx_color == 2 && input->input[input->y + 1] == 0)
		{
			if (check_the_rest_color(input->input[input->y]) != 2)
				break ;
		}
		input->y++;
	}
	if (idx_color != 2)
		return (1);
	set_color(a, &color);
	free(color.c);
	free(color.f);
	return (0);
}
