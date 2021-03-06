/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:34:57 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:34:57 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	hero(t_env *e)
{
	double		x;
	double		y;
	int			size;

	size = -3;
	x = e->h.y;
	y = -e->h.x + 1 + e->m.height;
	while (++size < 3)
	{
		put_pixel(x * e->m.size + e->m.offx + size,
				y * e->m.size + e->m.offy, 0xff66cc, e);
		put_pixel(x * e->m.size + e->m.offx,
				y * e->m.size + e->m.offy + size, 0xff66cc, e);
	}
}

int		place_hero(t_env *e)
{
	int	x;
	int	y;

	x = -1;
	while (++x < e->m.height)
	{
		y = -1;
		while (++y < e->m.width)
		{
			if (e->m.tab[x][y] < 0 || e->m.tab[x][y] > 9)
			{
				if ((e->m.tab[x][y] == 'x' - '0') ||
					(e->m.tab[x][y] == 'X' - '0'))
				{
					e->h.x = x + 0.5;
					e->h.y = y + 0.5;
					e->m.tab[x][y] = 0;
				}
				else
					return (0);
			}
		}
	}
	return (1);
}

void	block(int x, int y, int color, t_env *e)
{
	int		i;
	int		k;

	i = -1;
	while (++i < e->m.size)
	{
		k = -1;
		while (++k < e->m.size)
			put_pixel(x * e->m.size + e->m.offx + i,
					y * e->m.size + e->m.offy + k, color, e);
	}
}

void	color_map(int x, int y, t_env *e)
{
	int		rx;
	int		ry;

	rx = y;
	ry = -x + e->m.height;
	if (e->m.tab[x][y] == 0)
		block(rx, ry, 0x333e62, e);
	else if (e->m.tab[x][y] == 1)
		block(rx, ry, 0x828E96, e);
	else if (e->m.tab[x][y] == 2)
		block(rx, ry, 0xffb847, e);
	else if (e->m.tab[x][y] == 3)
		block(rx, ry, 0x828E96, e);
	else if (e->m.tab[x][y] == 4)
		block(rx, ry, 0x48dc64, e);
	else if (e->m.tab[x][y] == 5)
		block(rx, ry, 0x6e707d, e);
	else if (e->m.tab[x][y] == 6)
		block(rx, ry, 0x633d89, e);
	else if (e->m.tab[x][y] == 7)
		block(rx, ry, 0x319030, e);
	else if (e->m.tab[x][y] == 8)
		block(rx, ry, 0xb2199f, e);
	else if (e->m.tab[x][y] == 9)
		block(rx, ry, 0xfdff84, e);
}

void	minimap(t_env *e)
{
	int		x;
	int		y;

	x = -1;
	while (++x < e->m.width)
	{
		y = -1;
		while (++y < e->m.height)
			color_map(y, x, e);
	}
	hero(e);
}
