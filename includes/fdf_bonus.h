/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:50:52 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/22 14:41:24 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

# define WIDTH 1920
# define HEIGHT 1080

# define COL_DISCO		0x9A1F6AFF
# define COL_BRICK_RED	0xC2294EFF
# define COL_FLAMINGO	0xEC4B27FF
# define COL_JAFFA		0xEF8633FF
# define COL_SAFFRON	0xF3AF3DFF
# define COL_BG 		0x050203FF
# define COL_LINE		0xF8F7edFF
# define COL_LINE2		0x8B0000C8
# define COL_BLUE		0x1B03A3FF
# define COL_PINK		0xFFC0CBFF

# define ERR_INFILE "Invalid map"
# define ERR_ARG "Invalid amount of arguments"
# define ERR_MALLOC "Malloc error"
# define ERR_MLX "MLX error"

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int32_t	col;
	int32_t	col2;
	int		err;
	int		dx;
	int		dy;
}	t_point;

typedef struct s_proj
{
	double	alpha;
	double	beta;
	double	gamma;
	double	alphasave;
	double	betasave;
	double	gammasave;
}	t_proj;

typedef struct s_map
{
	mlx_t		*m;
	mlx_image_t	*image;
	double		z_factor;
	int			rows;
	int			cols;
	double		size_factor;
	t_point		**points;
	t_point		*start;
	t_point		*end;
	int			origox;
	int			origoy;
	int			offset_x;
	int			offset_y;
	t_proj		projection;
	int			highest_z;
	int			change;
	int			col_theme;
	bool		camera_dir;
}	t_map;

//Map parsing
void	count_columns(int fd, t_map *map, char **argv);
void	count_rows(int fd, t_map *map, char **argv);
void	fill_map(int fd, t_map *map, char **argv);

//Map drawing
void	draw_map(t_map *map);
void	set_offset(t_map *map);
int		pixel_ok(int x, int y);
int32_t	get_col(t_point *start, t_point *end, t_map *map);
void	bresenham_line(mlx_image_t *image, t_point s, t_point e, int32_t col);

//rotate and center
t_point	correct_point_offset(t_point *point, t_map *map);
t_point	rotate(t_point point, t_map *map);
t_point	rotate_x(t_point point, double angle);
t_point	rotate_y(t_point point, double angle);
t_point	rotate_z(t_point point, double angle);

//utils
int		ft_atoi_hex(char *str);
void	init_points(t_point *p1, t_point orig1, t_point *p2, t_point orig2);
int		absolute_value(int num);
void	check_array(char **rowarr, t_map *map);
void	set_colours(t_point *point);

//hooks
void	my_keyhook(void *param);
void	change_projection(t_map *map);
void	disco(t_map *map);
void	discomove(t_map *map);

//free and error
void	ft_free_map_and_array_error(t_map *map, char **array, char *error);
void	ft_free_map_and_exit(t_map *map);
void	ft_error(char *error);
void	ft_free_map_and_error(t_map *map, char *error);
void	ft_free_double_array(char **array);

#endif