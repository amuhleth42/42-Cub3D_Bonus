/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:39:17 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/22 15:10:53 by amuhleth         ###   ########.fr       */
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
	a->ui.x = WIN_WIDTH;
	a->ui.y = WIN_HEIGHT;
	a->ui.img = mlx_new_image(a->mlx, a->ui.x, a->ui.y);
	a->ui.addr = mlx_get_data_addr(a->ui.img, &a->ui.bpp, &a->ui.ll,
			&a->ui.endian);
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
	//a->map.floor = 0xAAAAAA;
	//a->map.ceiling = 0x666666;
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
	init_tile(&a->n, a->sprite.no, a->mlx);
	init_tile(&a->s, a->sprite.so, a->mlx);
	init_tile(&a->e, a->sprite.ea, a->mlx);
	init_tile(&a->w, a->sprite.we, a->mlx);
	//init_tile(&a->d, "assets/wolf3d/purplestone.XPM", a->mlx);
	if (!a->n.img || !a->s.img || !a->e.img || !a->w.img)
		ft_printf("Error: texture failed\n");
	a->n.addr = mlx_get_data_addr(a->n.img, &a->n.bpp, &a->n.ll, &a->n.endian);
	a->s.addr = mlx_get_data_addr(a->s.img, &a->s.bpp, &a->s.ll, &a->s.endian);
	a->e.addr = mlx_get_data_addr(a->e.img, &a->e.bpp, &a->e.ll, &a->e.endian);
	a->w.addr = mlx_get_data_addr(a->w.img, &a->w.bpp, &a->w.ll, &a->w.endian);
	//a->d.addr = mlx_get_data_addr(a->d.img, &a->d.bpp, &a->d.ll, &a->d.endian);
}

void	init_game(t_data *a)
{
	//a->cam.x = 170.0;
	//a->cam.y = 170.0;
	//a->cam.a = 0.0;
	a->cam.dx = cos(a->cam.a);
	a->cam.dy = sin(a->cam.a);
	a->cam.size = 4;
	a->diff = 16;
	a->cam.color = 0xFFFF00;
	a->mouse.x = WIN_WIDTH / 2;
	a->mouse.y = WIN_HEIGHT / 2;
	render_frame(a);
}

void	init_threads(t_data *a)
{
	a->thread = ft_calloc(NB_THREAD + 1, sizeof(t_thread));
	if (!a->thread)
		exit_all(a);
	//ft_printf("thread init done\n");
}

int	main(int argc, char **argv)
{
	t_data	a;

	ft_bzero(&a, sizeof(a));
	gettimeofday(&a.start, NULL);
	gettimeofday(&a.frame, NULL);
	parser(argc, argv, &a);
	init_map(&a);
	init_graphics(&a);
	init_threads(&a);
	init_textures(&a);
	init_game(&a);
	mlx_mouse_hide();
	mlx_mouse_move(a.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	init_mlx_hooks(&a);
}
