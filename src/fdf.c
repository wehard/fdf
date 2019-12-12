/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/12 14:36:17 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "fdf.h"
#include "libft.h"
#include "mlx.h"

int		on_render(void *param)
{
	t_fdf_data *fdf_data;

	fdf_data = (t_fdf_data*)param;
	if (!fdf_data || !fdf_data->map)
		return (0);
	clear_frame_buffer(fdf_data->f_buf);
	ft_draw_map(fdf_data);
	if (fdf_data->show_info)
		ft_draw_axis(fdf_data, fdf_data->map->pos, fdf_data->map->rot, 10.0f);
	if (fdf_data->f_buf->img)
		mlx_put_image_to_window(fdf_data->mlx_ptr, fdf_data->win_ptr,
			fdf_data->f_buf->img, 0, 0);
	if (fdf_data->show_info)
		ft_draw_info(fdf_data);
	return (0);
}

int		main(int argc, char const *argv[])
{
	t_fdf_data	*fdf_data;
	t_map		*map;
	int			fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 3 || !read_map_file(fd, &map, BLUE, WHITE))
		{
			close(fd);
			return (throw_error("error: map error"));
		}
	}
	else
		return (throw_error("usage: ./fdf mapfile"));
	if (!(fdf_data = init_fdf_data("fdf", map)))
		return (throw_error("fdf: failed to init!"));
	mlx_hook(fdf_data->win_ptr, 2, 0, on_key_down, (void*)fdf_data);
	mlx_loop_hook(fdf_data->mlx_ptr, on_render, (void*)fdf_data);
	mlx_loop(fdf_data->mlx_ptr);
	return (0);
}
