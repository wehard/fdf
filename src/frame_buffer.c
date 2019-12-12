/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 10:34:47 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/12 16:31:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "fdf.h"
#include "libft.h"

void			frame_buffer_set(t_frame_buffer *fb, int x, int y, int c)
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	*(int*)(fb->d_addr + (((y * WIN_W) + x) * fb->bpp)) = c;
}

t_frame_buffer	*create_frame_buffer(t_fdf_data *fdf_data)
{
	t_frame_buffer *fb;

	if (!(fb = (t_frame_buffer*)malloc(sizeof(t_frame_buffer))))
	{
		throw_error("error: create frame buffer failed!");
		return (NULL);
	}
	fb->w = WIN_W;
	fb->h = WIN_H;
	if (!(fb->img = mlx_new_image(fdf_data->mlx_ptr, fb->w, fb->h)))
	{
		throw_error("error: mlx_new_image failed!");
		return (NULL);
	}
	if (!(fb->d_addr = mlx_get_data_addr(fb->img, &fb->bpp,
										&fb->size_line, &fb->endian)))
	{
		throw_error("error: mlx_get_data_addr failed!");
		return (NULL);
	}
	fb->bpp /= 8;
	return (fb);
}

void			clear_frame_buffer(t_frame_buffer *fb)
{
	if (!fb || !fb->d_addr)
		return ;
	ft_bzero(fb->d_addr, fb->w * fb->h * fb->bpp);
}
