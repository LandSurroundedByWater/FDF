/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:10:01 by tsaari            #+#    #+#             */
/*   Updated: 2024/03/16 12:11:30 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_line(t_line *line, t_point start, t_point end)
{
	int temp;

	line->dx = end.x - start.x;
	line->dy = end.y - start.y;
	line->p = 0;
	line->swapped = 0;
	if(line->dx < 0)
		line->dx *= -1;
	if(line->dy < 0)
		line->dy *= -1;
	if(line->dy > line->dx)
	{
		temp = line->dx;
		line->dx = line->dy;
		line->dy = temp;
		line->swapped = 1;
	}
}

void	init_points(t_point *p1, t_point orig1, t_point *p2, t_point orig2)
{
	p1->col = orig1.col;
	p1->col2 = orig1.col2;
	p1->x = orig1.x;
	p1->y = orig1.y;
	p1->z = orig1.z;
	p1->col_theme = orig1.col_theme;
	p2->col = orig2.col;
	p2->col2 = orig2.col2;
	p2->x = orig2.x;
	p2->y = orig2.y;
	p2->z = orig2.z;
	p2->col_theme = orig2.col_theme;
}