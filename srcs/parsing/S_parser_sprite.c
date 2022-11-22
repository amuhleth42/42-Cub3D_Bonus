/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdi-noce <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:39:59 by kdi-noce          #+#    #+#             */
/*   Updated: 2022/11/22 13:44:05 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_the_rest_sprite(char *input)
{
	char	**new_array;
	int		args;
	int 	i;

	args = 0;
	i = -1;
	new_array = ft_split(input, ' ');
	while (new_array[args])
		args++;
	while (new_array[++i])
		free(new_array[i]);
	return (args);
}

int	check_sprite(char *array, t_text *dirct, t_sprite *sprite)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = check_space(array, 1);
	if (!ft_isalpha(array[i]) && array[i])
		array = check_space(array, 0);
	if (!dirct->no || !dirct->so || !dirct->we || !dirct->ea)
	{
		if (!array || !tmp)
			return (0);
	}
	if (!ft_strncmp(array, "NO", 2))
		manage_path_dirct_s(sprite, dirct, tmp, 1);
	else if (!ft_strncmp(array, "SO", 2))
		manage_path_dirct_s(sprite, dirct, tmp, 2);
	else if (!ft_strncmp(array, "WE", 2))
		manage_path_dirct_s(sprite, dirct, tmp, 3);
	else if (!ft_strncmp(array, "EA", 2))
		manage_path_dirct_s(sprite, dirct, tmp, 4);
	if (dirct->no == 1 && dirct->so == 1 && dirct->we == 1 && dirct->ea == 1)
		return (4);
	return (0);
}
//printf("NO=%d	SO=%d	WE=%d	EA=%d\n",
// dirct->no, dirct->so, dirct->we, dirct->ea);

int	parse_sprite(t_args *input, t_sprite *sprite)
{
	int			idx_text;
	t_text		dirct;

	input->y = 0;
	idx_text = 0;
	struct_init(&dirct);
	while (input->input[input->y] && input->input[input->y][0])
	{
		//printf("%s\n", input->input[input->y]);
		idx_text = check_sprite(input->input[input->y], &dirct, sprite);
		if (idx_text == 4 && input->input[input->y + 1] == 0)
		{
			if ((check_the_rest_sprite(input->input[input->y]) == 2))
				break ;
		}
		input->y++;
	}
	if (idx_text != 4)
		return (1);
	return (0);
}
