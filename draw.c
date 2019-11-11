/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:06:16 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/11 13:17:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** plotLineLow(x0,y0, x1,y1)
**   dx = x1 - x0
**   dy = y1 - y0
**   yi = 1
**   if dy < 0
**     yi = -1
**     dy = -dy
**   end if
**   D = 2*dy - dx
**   y = y0
**
**   for x from x0 to x1
**     plot(x,y)
**     if D > 0
**        y = y + yi
**        D = D - 2*dx
**     end if
**     D = D + 2*dy
*/

void	draw_line(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1)
{
	float x;
	float y;
	float deltaX;
	float deltaY;
	float yintercept;
	float D;
	deltaX = p1.x - p0.x;
	deltaY = p1.y - p0.y;
	yintercept = 1;
	if (deltaY < 0.0f)
	{
		yintercept = -1.0f;
		deltaY = -deltaY;
	}
	D = 2.0f * deltaY - deltaX;
	y = p0.y;
	x = p0.x;
	while (x < p1.x)
	{
		//mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, x, y, GREEN);
		frame_buffer_set(fb, x, y, GREEN);
		if (D > 0.0f)
		{
			y = y + yintercept;
			D = D - 2.0f * deltaX;
		}
		D = D + 2.0f * deltaY;
		x++;
	}
}

void	draw_tri(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1, t_vec3 p2)
{
	draw_line(fb, p0, p1);
	draw_line(fb, p1, p2);
	draw_line(fb, p2, p0);
}

void	draw_quad(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1, t_vec3 p2, t_vec3 p3)
{
	draw_line(fb, p0, p1);
	draw_line(fb, p1, p2);
	draw_line(fb, p2, p3);
	draw_line(fb, p3, p0);
}
