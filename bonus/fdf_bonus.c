/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:57:40 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/28 09:56:59 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static void	init_z_factor(t_map *map)
{
	if (map->highest_z > 140)
		map->z_factor = 0.3;
}

static void	init_map(int fd, t_map *map, char **argv)
{
	map->cols = 0;
	map->rows = 0;
	map->points = NULL;
	map->projection.alpha = 0.45;
	map->projection.beta = -0.35264;
	map->projection.gamma = 0.45;
	map->z_factor = 5;
	map->col_theme = 1;
	count_rows(fd, map, argv);
	count_columns(fd, map, argv);
	map->size_factor = (WIDTH - WIDTH / 3) / map->cols;
	map->origox = WIDTH / 2;
	map->origoy = HEIGHT / 2;
	map->camera_dir = true;
}

static void	allocate_map(t_map *map)
{
	int	i;

	i = 0;
	map->start = malloc(sizeof(t_point));
	map->end = malloc(sizeof(t_point));
	map->points = (t_point **)malloc(map->rows * sizeof(t_point *));
	if (map->points == NULL)
		ft_free_map_and_error(map, ERR_MALLOC);
	while (i < map->rows)
	{
		map->points[i] = (t_point *)malloc((map->cols + 1) * sizeof(t_point));
		if (!map->points[i])
			ft_free_map_and_error(map, ERR_MALLOC);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_map	*map;
	int		fd;

	fd = 0;
	if (argc != 2)
		ft_error(ERR_ARG);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_error(ERR_MALLOC);
	else
	{
		init_map(fd, map, argv);
		allocate_map(map);
		fill_map(fd, map, argv);
		init_z_factor(map);
		map->m = mlx_init(WIDTH, HEIGHT, argv[1], false);
		if (!map->m)
			ft_free_map_and_error(map, ERR_MLX);
		mlx_loop_hook(map->m, my_keyhook, map);
		mlx_loop(map->m);
		mlx_terminate(map->m);
	}
	ft_free_map_and_exit(map);
}
