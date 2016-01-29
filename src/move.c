/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkalb <fkalb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 19:07:01 by fkalb             #+#    #+#             */
/*   Updated: 2015/03/07 22:19:08 by fkalb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		move(t_all *all, short int dir)
{
	int		speed;
	t_point	*tmp;

	speed = 5 * all->ratio;
	speed = speed > 15 ? 15 : speed;
	speed = speed < 5 ? 5 : speed;
	tmp = all->start;
	while (tmp)
	{
		if (dir == 0)
			tmp->col -= speed;
		else if (dir == 1)
			tmp->line -= speed;
		else if (dir == 2)
			tmp->col += speed;
		else if (dir == 3)
			tmp->line += speed;
		tmp = tmp->next;
	}
}
