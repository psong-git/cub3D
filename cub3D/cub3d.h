/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 21:21:47 by paul              #+#    #+#             */
/*   Updated: 2021/05/31 15:50:59 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# define NONE 0xFF000000
# define FOV 60
# define WALL_H 1.0
# define TWOPI 6.28318530717958647692
# define ROTUNIT 0.03
# define MOVEUNIT 0.2

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define ESC 53
# define Q	12
# define W	13
# define E	14
# define R	15
# define A	0
# define S	1
# define D	2
# define LEFT 123
# define RIGHT 124
# define TEXWIDTH 64
# define TEXHEIGHT 64

# define FALSE 0
# define TRUE 1
# define VERT 0
# define HORIZ 1
# define DIR_N 0
# define DIR_E 1
# define DIR_W 2
# define DIR_S 3

typedef struct	s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct	s_win
{
	void			*ptr;
	int				x;
	int				y;
	double			a_p_pixel;
	double			p_p_angle;
	double			fov_h;
	double			fov_v;
	double			fovh_2;
}				t_win;

typedef struct	s_img
{
	void			*ptr;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
}				t_img;

typedef struct	s_err
{
	int				n;
	int				m;
	int				p;
	int				r;
}				t_err;

typedef struct	s_map
{
	char			**tab;
	int				x;
	int				y;
	int				l;
}				t_map;

typedef struct	s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*i;
	unsigned int	c;
	unsigned int	f;
	int				tx;
	int				ty;
	double			wx;
	double			wy;
	int				**visible;
	double			*zbuf;
	int				pcnt;
}				t_tex;

typedef struct	s_pos
{
	double			x;
	double			y;
	double			th;
}				t_pos;

typedef struct	s_spr
{
	int				tex;
	int				x;
	int				y;
	double			dist;
	double			th;
	int				tx;
	int				ty;
	int				sh;
}				t_spr;

typedef struct	s_w
{
	int				xstep;
	int				ystep;
	double			xslope;
	double			yslope;
	double			nx;
	double			ny;
	double			f;
	double			g;
	int				hit;
	int				hit_side;
	int				mapx;
	int				mapy;
}				t_w;

typedef struct	s_all
{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
	t_err			err;
	t_map			map;
	t_tex			tex;
	t_spr			*spr;
	t_pos			pos;
	t_w				w;
}				t_all;

void			ft_init(char *cub, int bmp);
void			ft_declare(t_all s, char *cub, int bmp);
int				ft_cubed(t_all s, char *cub, int bmp);
void			ft_draw(t_all *s);
int				ft_namecheck(char *arg, char *ext);
int				ft_savecheck(char *arg, char *save);
int				ft_parse(t_all *s, char *cub);
int				ft_line(t_all *s, char *line);
int				ft_map(t_all *s, char *line, int *i);
char			*ft_slab(t_all *s, char *line, int *i);
int				ft_slablen(t_all *s, char *line);
int				ft_texture(t_all *s, unsigned int **adr, char *line, int *i);
int				ft_xpm(t_all *s, unsigned int **adr, char *file);
int				ft_slist(t_all *s);
void			ft_pos(t_all *s, int i, int j, double th);
int				ft_colors(unsigned int *color, char *line, int *i);
int				ft_res(t_all *s);
int				ft_parcheck(t_all *s);
int				ft_mapcheck1(t_all *s, int a, int b, int c);
void			ft_mapcheck2(t_all *s, int a, int b, int *c);
int				ft_key(int key, void *arg);
void			ft_rotate(t_all *s, double c);
void			ft_strafe(t_all *s, double c);
void			ft_move(t_all *s, double c);
int				ft_close(t_all *s, int win);
void			ft_ray(t_all *s);
void			ft_sprite(t_all *s);
void			ft_sdraw(t_all *s, int loc, double dist);
unsigned int	ft_spixel(t_all *s, int index, unsigned int col);
int				ft_bitmap(t_all *s);
void			ft_bdraw(t_all *s);
void			ft_bfile(t_all *s, int fd);
void			ft_binfo(t_all *s, int fd);
void			ft_bdata(t_all *s, int fd);
int				ft_atoi(char *line, int *i);
int				ft_spaceskip(char *line, int *i);
int				ft_strerror(int err);
int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dest, const char *src, size_t dstsize);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char *s1, char *s2);
int				map_get_cell(t_all *s, int x, int y);
int				sgn(double d);
double			l2dist(double x0, double y0, double x1, double y1);
double			cast_single_ray(t_all *s, int x, int *wdir);
int				get_wall_intersection(t_all *s, double ray, int *wdir);
int				get_wall_intersection2(t_all *s, double ray, int *wdir);
void			get_wall_intersection3(t_all *s, int *wdir, int cell);
int				get_wall_intersection4(t_all *s, int cell,
		double dist_v, double dist_h);
int				get_wall_height(t_all *s, double dist);
void			draw_wall(t_all *s, double wdist, int x, int color);
void			render(t_all *s);
int				key_press(int key, t_all *s);
int				key_release(int key, t_all *s);
void			player_rotate(t_all *s, double th);
int				get_move_offset(double th, int key,
			double *pdx, double *pdy);
int				player_move(t_all *s, int key);
void			get_visible_sprites(t_all *s, int *pcnt, int x, int y);
void			get_visible_sprites2(t_all *s, int n, int x, int y);
int				cmp_sprites(const void *a, const void *b);
void			draw_sprites(t_all *s);
void			draw_sprites2(t_all *s, int cx, int sh, int i);
void			map_extend(t_all *s, int a, int b, int i);
int				sprite_init(t_all *s);
double			deg2rad(double d);
double			rad2deg(double d);
double			min(double a, double b);
double			max(double a, double b);
void			wall_init(t_all *s);
#endif
