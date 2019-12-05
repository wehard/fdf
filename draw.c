/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:06:16 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/05 16:13:35 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_low(t_frame_buffer *fb, t_intvec2 p0, t_intvec2 p1, t_rgba c1, t_rgba c2)
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
		float t = ft_convert_range(p.x, p0.x, p1.x, 0.0f, 1.0f);
		int c = ft_get_color(ft_lerp_rgba(c1, c2, t));
		frame_buffer_set(fb, p.x, p.y, c);
		if (d > 0)
		{
			p.y = p.y + yi;
			d = d - (2 * dx);
		}
		d = d + (2 * dy);
		p.x++;
	}
}

static void	draw_line_high(t_frame_buffer *fb, t_intvec2 p0, t_intvec2 p1, t_rgba c1, t_rgba c2)
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
		float t = ft_convert_range(p.y, p0.y, p1.y, 0.0f, 1.0f);
		int c = ft_get_color(ft_lerp_rgba(c1, c2, t));
		frame_buffer_set(fb, p.x, p.y, c);
		if (d > 0)
		{
			p.x = p.x + xi;
			d = d - (2 * dy);
		}
		d = d + (2 * dx);
		p.y++;
	}
}

void	draw_line(t_frame_buffer *fb, t_intvec2 p0, t_intvec2 p1, t_rgba c1, t_rgba c2)
{
	if (abs(p1.y - p0.y) < abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			draw_line_low(fb, p1, p0, c2, c1);
		else
			draw_line_low(fb, p0, p1, c1, c2);
	}
	else
	{
		if (p0.y > p1.y)
			draw_line_high(fb, p1, p0, c2, c1);
		else
			draw_line_high(fb, p0, p1, c1, c2);
	}
}

