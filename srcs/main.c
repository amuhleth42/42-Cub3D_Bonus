/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:39:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/16 14:39:32 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_graphics(t_data *a)
{
	a->mlx = mlx_init();
	a->win = mlx_new_window(a->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	a->fp.x = WIN_WIDTH;
	a->fp.y = WIN_HEIGHT;
	a->fp.img = mlx_new_image(a->mlx, a->fp.x, a->fp.y);
	a->fp.addr = mlx_get_data_addr(a->fp.img, &a->fp.bpp, &a->fp.ll,
			&a->fp.endian);
	a->mini.x = a->map.x * a->map.size;
	a->mini.y = a->map.y * a->map.size;
	a->mini.img = mlx_new_image(a->mlx, a->mini.x, a->mini.y);
	a->mini.addr = mlx_get_data_addr(a->mini.img, &a->mini.bpp, &a->mini.ll,
			&a->mini.endian);
}

void	init_mlx_hooks(t_data *a)
{
	mlx_hook(a->win, ON_KEYDOWN, 0, &key_down, a);
	mlx_hook(a->win, ON_KEYUP, 0, &key_up, a);
	mlx_hook(a->win, ON_DESTROY, 0, &red_cross, a);
	mlx_loop_hook(a->mlx, &loop_render, a);
	mlx_loop(a->mlx);
}

void	init_map(t_data *a)
{
	a->map.map = ft_calloc(42, sizeof(char *));
	if (!a->map.map)
		exit(1);

	a->map.map[0] = "1111111111111111111111111111111111111111111111111111111111111111";
	a->map.map[1] = "1000000000000001000000000000001000000000000000001000000000000001";
	a->map.map[2] = "1000000000000000000000000000000000000000000000000000000000000001";
	a->map.map[3] = "1000000000000001000000000000001000000000000000001000000000000001";
	a->map.map[4] = "1000001100000111111111111111111111111100011111111110111111110111";
	a->map.map[5] = "1000001100000111111111111111111111111100010011111100011111100011";
	a->map.map[6] = "1000001100000000000000000000000001111110110010000000000000000001";
	a->map.map[7] = "1000001100000000000000000000000001100100011000000000000000000001";
	a->map.map[8] = "1000001100000000000000000000000001100100011010000000000000000001";
	a->map.map[9] = "1000001100000111111111111111111011111100011111111111111111111111";
	a->map.map[10] = "1000001100000100000000111111100001100000001111000000000000000001";
	a->map.map[11] = "1000001100000000000000111111100001111100011111000000000000000001";
	a->map.map[12] = "1000001100000100000000110001100001111100011111000000000000000001";
	a->map.map[13] = "1000001111111111111111110001111111111100011111111111111111111111";
	a->map.map[14] = "1000001000001111111111110001111111111110111111111111111111111111";
	a->map.map[15] = "1000001000001100000000011011000000001100010000000000000000000011";
	a->map.map[16] = "1000001000001100000000010001000000001100010000000000000000000011";
	a->map.map[17] = "1000000000001100000000000000000000001100010000000000000000000001";
	a->map.map[18] = "1000000000001100000000010001000000001100010000000000000000000011";
	a->map.map[19] = "1000001000001100000000000000000000001100010000000000000000000001";
	a->map.map[20] = "1000001000001100000000010001000000000100011111101111111110111111";
	a->map.map[21] = "1111101111111100000000110001100000000100010000000000000000000001";
	a->map.map[22] = "1110000011111111111111100000111111111100010000000000000000000001";
	a->map.map[23] = "1110000011000100000000000000000000000100010000000000000000000001";
	a->map.map[24] = "1010000011000000000000000000000000000000010000000000000000000001";
	a->map.map[25] = "1000000011000100000000000000000000000100010000000000000000000001";
	a->map.map[26] = "1010000011000111111000000000000011111100010000000000000000000001";
	a->map.map[27] = "1110000011000000011111111011111110000100011101111111111111110111";
	a->map.map[28] = "1110000011000000011000010001000010000100010000000000000000000001";
	a->map.map[29] = "1111111111111111011000000000000010000100010000000000000000000001";
	a->map.map[30] = "1111111111111110001000010001000010000100010000000000000000000001";
	a->map.map[31] = "1011110000100010001111110001111110000100011000000000000000000001";
	a->map.map[32] = "1000010000100010001000010001000010000100011000000000000000000001";
	a->map.map[33] = "1000011101110110001000000000000010000100011000000000000000000001";
	a->map.map[34] = "1000000000000010001000010001000010000100011000000000000000000001";
	a->map.map[35] = "1000000000000000001111110001111110000100011110001100011110001111";
	a->map.map[36] = "1000000000000010001000010001000010000100011111011110111111011111";
	a->map.map[37] = "1000011101110110001000000000000011110100000000000000011000000011";
	a->map.map[38] = "1000010000100010001000010001000011100100000000000000011000000111";
	a->map.map[39] = "1000010000100011111111111111111111111100000000000000011000000011";
	a->map.map[40] = "1111111111111111111111111111111111111111111111111111111111111111";
	a->map.x = 64;
	a->map.y = 41;
	a->map.floor = 0xAAAAAA;
	a->map.ceiling = 0x666666;
	a->map.border = 1;
	if (a->map.x <= 10 && a->map.y <= 16)
		a->map.size = 20;
	else if (a->map.x <= 20 && a->map.y <= 32)
		a->map.size = 10;
	else if (a->map.x <= 430 && a->map.y <= 64)
	{
		a->map.size = 5;
		a->map.border = 0;
	}
}

void	init_tile(t_img *img, char *file, void *mlx)
{
	img->img = mlx_xpm_file_to_image(mlx, file, &img->x, &img->y);
}

void	init_textures(t_data *a)
{
	init_tile(&a->n, "assets/wolf3d/bluestone.XPM", a->mlx);
	init_tile(&a->s, "assets/wolf3d/colorstone.XPM", a->mlx);
	init_tile(&a->e, "assets/wolf3d/purplestone.XPM", a->mlx);
	init_tile(&a->w, "assets/wolf3d/redbrick.XPM", a->mlx);
	/*if (!a->map.n.img)
	{
		ft_printf("Error: texture failed\n");
		exit(0);
	}*/
	a->n.addr = mlx_get_data_addr(a->n.img, &a->n.bpp, &a->n.ll, &a->n.endian);
	a->s.addr = mlx_get_data_addr(a->s.img, &a->s.bpp, &a->s.ll, &a->s.endian);
	a->e.addr = mlx_get_data_addr(a->e.img, &a->e.bpp, &a->e.ll, &a->e.endian);
	a->w.addr = mlx_get_data_addr(a->w.img, &a->w.bpp, &a->w.ll, &a->w.endian);
}

void	init_game(t_data *a)
{
	a->cam.x = 170.0;
	a->cam.y = 170.0;
	a->cam.a = 0.0;
	a->cam.dx = cos(a->cam.a);
	a->cam.dy = sin(a->cam.a);
	a->cam.size = 4;
	a->cam.color = 0xFFFF00;
	render_frame(a);
}

void	init_threads(t_data *a)
{
	a->thread = ft_calloc(NB_THREAD + 1, sizeof(t_thread));
	if (!a->thread)
		exit_all(a);
	ft_printf("thread init done\n");
}

int	main(int argc, char **argv)
{
	t_data	a;

	(void)argc;
	(void)argv;
	ft_bzero(&a, sizeof(a));
	gettimeofday(&a.start, NULL);
	gettimeofday(&a.frame, NULL);
	init_map(&a);
	init_graphics(&a);
	init_threads(&a);
	init_textures(&a);
	init_game(&a);
	init_mlx_hooks(&a);
}
