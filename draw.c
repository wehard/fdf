/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:06:16 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/29 23:45:26 by wkorande         ###   ########.fr       */
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

void	draw_line_low(t_frame_buffer *fb, t_intvec2 p0, t_intvec2 p1, int color)
{
	t_intvec2 p;
	int dx;
	int dy;
	int yi;
	int d;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = 2 * dy - dx;
	p.y = p0.y;
	p.x = p0.x;
	while (p.x < p1.x)
	{
		frame_buffer_set(fb, p.x, p.y, color);
		if (d > 0)
		{
			p.y = p.y + yi;
			d = d - (2 * dx);
		}
		d = d + (2 * dy);
		p.x++;
	}
}

/*
** plotLineHigh(x0,y0, x1,y1)
**   dx = x1 - x0
**   dy = y1 - y0
**   xi = 1
**   if dx < 0
**     xi = -1
**     dx = -dx
**   end if
**   D = 2*dx - dy
**   x = x0
**
**   for y from y0 to y1
**     plot(x,y)
**     if D > 0
**        x = x + xi
**        D = D - 2*dy
**     end if
**     D = D + 2*dx
*/

void	draw_line_high(t_frame_buffer *fb, t_intvec2 p0, t_intvec2 p1, int color)
{
	t_intvec2 p;
	int dx;
	int dy;
	int xi;
	int d;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = 2 * dx - dy;
	p.x = p0.x;
	p.y = p0.y;
	while (p.y < p1.y)
	{
		frame_buffer_set(fb, p.x, p.y, color);
		if (d > 0)
		{
			p.x = p.x + xi;
			d = d - (2 * dy);
		}
		d = d + (2 * dx);
		p.y++;
	}
}

void	draw_line(t_frame_buffer *fb, t_intvec2 p0, t_intvec2 p1, int color)
{
	if (abs(p1.y - p0.y) < abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			draw_line_low(fb, p1, p0, color);
		else
			draw_line_low(fb, p0, p1, color);
	}
	else
	{
		if (p0.y > p1.y)
			draw_line_high(fb, p1, p0, color);
		else
			draw_line_high(fb, p0, p1, color);
	}
}

void	draw_line_simple(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1)
{
	float x;
	float slope;
	float yintercept;
	float y;

	if (p1.z > 0)
			p1.y -= 5;
	x = p0.x;
	slope = (p1.y - p0.y) / (p1.x - p0.x);
	yintercept = p0.y;
	while (x < p1.x)
	{
		y = slope * x + yintercept;
		frame_buffer_set(fb, x, y, GREEN);
		x++;
	}
}

void	draw_tri(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1, t_vec3 p2)
{
	//draw_line(fb, p0, p1);
	//draw_line(fb, p1, p2);
	//draw_line(fb, p2, p0);
}

void	draw_quad(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1, t_vec3 p2, t_vec3 p3)
{
	//draw_line(fb, p0, p1);
	//draw_line(fb, p1, p2);
	//draw_line(fb, p2, p3);
	//draw_line(fb, p3, p0);
}
