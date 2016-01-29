/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkalb <fkalb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 14:16:42 by fkalb             #+#    #+#             */
/*   Updated: 2015/03/07 23:35:39 by fkalb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"
#include "get_next_line.h"

void	add_elem(t_point **start, int col, int line, char *s)
{
	t_point	*elem;
	t_point *new;

	elem = *start;
	while (elem->next)
	{
		elem = elem->next;
	}
	new = (t_point*)malloc(sizeof(t_point));
	new->line = line;
	new->col = col;
	new->next = NULL;
	new->down = NULL;
	new->high = ft_atoi(s);
	if (new->high < -1)
		new->color = BLUE;
	else if (new->high <= 30)
		new->color = GREEN;
	else if (new->high <= 42)
		new->color = BROWN;
	else if (new->high > 50)
		new->color = WHITE;
	else
		new->color = GREY;
	elem->next = new;
}

void	setdown(t_point **start)
{
	t_point	*up;
	t_point	*elem;

	elem = *start;
	while (elem->next && (elem->line != 1))
	{
		elem = elem->next;
	}
	up = *start;
	up = up->next;
	while (elem)
	{
		up->down = elem;
		up = up->next;
		elem = elem->next;
	}
}

void	get_map(int fd, t_point **start, t_all *all)
{
	char	*str;
	char	**tab;
	int		i;
	int		line;

	line = 0;
	while (gnl(fd, &str) > 0 && ((tab = ft_strsplit(str, ' ')) != NULL))
	{
		i = 0;
		while (tab && tab[i])
		{
			add_elem(start, i, line, tab[i]);
			i++;
		}
		line++;
		all->cols = i;
		all->lines = line;
	}
	if (line > 0)
		setdown(start);
}
