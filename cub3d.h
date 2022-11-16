/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:38:51 by amuhleth          #+#    #+#             */
/*   Updated: 2022/11/16 14:27:58 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <pthread.h>
# include <sys/time.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 800

# define PI 3.1415926535

# define VIEW_FIELD	(PI / 3)
# define COLUMN_SIZE 2

# define NB_THREAD 12

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_DESTROY = 17
};

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		x;
	int		y;
}			t_img;

typedef struct s_cam
{
	float		x;
	float		y;
	int		size;
	int		color;
	float		dx;
	float		dy;
	float		a;
}			t_cam;

typedef struct s_ray
{
	float	x;
	float	y;
	float	xoff;
	float	yoff;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	hdist;
	float	vdist;
	float	dist;
	char	side;
	int		offset;
	float	size;
	float	step;
	float	tx;
	float	ty;
	float	tyoff;
	float	value;
}			t_ray;

typedef struct s_map
{
	char	**map;
	int		x;
	int		y;
	int		size;
	int		border;
	int		floor;
	int		ceiling;
}			t_map;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}		t_keys;

typedef struct s_data	t_data;

typedef struct s_thread
{
	int			nb;
	pthread_t	tid;
	t_data		*backup;
	int			nb_column;
	int			slice_size;
	float		slice_a;
}				t_thread;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_thread	*thread;
	t_map		map;
	t_img		mini;
	t_img		fp;
	t_cam		cam;
	t_keys		keys;
	t_img		n;
	t_img		s;
	t_img		e;
	t_img		w;
	struct timeval	start;
	struct timeval	last_frame;
	struct timeval	frame;
}				t_data;

//	utils.c

void	put_pixel(t_img *i, int x, int y, int color);
float	add_rad(float a1, float a2);
float	dist(float ax, float ay, float bx, float by);

//	draw_minimap.c

void	draw_cam(t_data *a);
void	draw_map(t_data *a);
void	draw_tile(t_data *a, int x, int y, int color);
void	draw_point(t_data *a, int x, int y);

//	render_column.c

void	render_column(t_data *a, t_ray *r, int i, t_img *img);

//	draw_column.c

void	draw_ceiling(t_data *a, t_ray *r, int index);
void	draw_column(t_data *a, t_ray *r, int index, t_img *img);
void	draw_floor(t_data *a, t_ray *r, int index);

//	exit.c

void	exit_all(t_data *a);
int		red_cross(t_data *a);

//	keyboard.c

int		key_down(int key, t_data *a);
int		key_up(int key, t_data *a);

//	move.c

void	move(t_data *a, int dir);
void	rl_move(t_data *a, int dir);
void	rotate(t_data *a, double da);
void	reset_screen(t_data *a);
float	add_rad(float a1, float a2);

//	ray.c

void	cast_ray(t_data *a, float ra, int i);
void	raycasting(t_data *a);

//	ray2.c

void	set_horizontal_start(t_data *a, t_ray *r, float ra);
void	set_vertical_start(t_data *a, t_ray *r, float ra);
void	horizontal_check(t_data *a, t_ray *r, float ra);
void	vertical_check(t_data *a, t_ray *r, float ra);

//	render.c

int		loop_render(t_data *a);
void	render_frame(t_data *a);
void	clear_img(t_img *i);

#endif
