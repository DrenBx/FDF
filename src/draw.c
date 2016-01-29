/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkalb <fkalb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 13:56:55 by fkalb             #+#    #+#             */
/*   Updated: 2015/03/08 01:01:29 by fkalb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void	drawtoimage(t_all *all, int x, int y, int color)
{
	int		i;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return ;
	i = y * (WIDTH * 4) + 4 * x;
	if ((i > (HEIGHT * (WIDTH * 4) + (WIDTH * 4))) || i < 0)
		return ;
	all->data[i] = color;
	all->data[i + 1] = color >> 8;
	all->data[i + 2] = color >> 16;
}

void	putpixright(t_all *all, t_point *elem)
{
	double	x;
	double	y;

	x = elem->posx;
	while (x <= elem->next->posx)
	{
		y = elem->posy + ((elem->next->posy - elem->posy) * (x - elem->posx))
			/ (elem->next->posx - elem->posx);
		drawtoimage(all, (int)x, (int)y, elem->color);
		x++;
	}
	x = elem->posx;
	y = elem->posy;
	while (y <= elem->next->posy)
	{
		x = elem->posx + ((elem->next->posx - elem->posx) * (y - elem->posy))
			/ (elem->next->posy - elem->posy);
		drawtoimage(all, (int)x, (int)y, elem->color);
		y++;
	}
}

void	putpixdown(t_all *all, t_point *elem)
{
	double	x;
	double	y;
	double	a;
	double	b;

	x = elem->posx;
	y = elem->posy;
	a = (y - elem->down->posy) / (x - elem->down->posx);
	b = elem->posy - (a * x);
	while (x >= elem->down->posx)
	{
		y = a * x + b;
		if ((y > 0) && (y < HEIGHT))
			drawtoimage(all, (int)x, (int)y, elem->color);
		x--;
	}
	x = elem->posx;
	y = elem->posy;
	while (y <= elem->down->posy)
	{
		x = (y - b) / a;
		if ((x > 0) && (x < WIDTH))
			drawtoimage(all, (int)x, (int)y, elem->color);
		y++;
	}
}

void	isoposition(t_all *all, t_point *elem, double x, double y)
{
	float	high;

	(void)all;
	high = elem->high;
	high = (all->active_neg == -1) && (high < 0) ? 0 : high;
	elem->posx = 0.7 * ((elem->col * x) - (0.8 * (elem->line * y)));
	elem->posy = -(float)high + ((0.35) * (x * elem->col))
		+ (0.4 * elem->line * y);
	elem->posx += WIDTH / 2.8;
	elem->posy += HEIGHT / 32;
}

void	putpoints(t_all *all, t_point **start)
{
	t_point	*elem;
	double	x;
	double	y;

	elem = *start;
	x = (WIDTH / (all->cols - 1)) + all->ratio;
	y = (HEIGHT / (all->lines - 1)) + (all->ratio * 2);
	while (elem)
	{
		isoposition(all, elem, x, y);
		elem = elem->next;
	}
	elem = *start;
	while (elem)
	{
		if (elem->next && (elem->next->line == elem->line))
			putpixright(all, elem);
		if (elem->down)
			putpixdown(all, elem);
		elem = elem->next;
	}
}
