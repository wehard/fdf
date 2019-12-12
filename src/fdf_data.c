/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:35:25 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/12 14:41:15 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

t_fdf_data	*init_fdf_data(char *title, t_map *map)
{
	t_fdf_data	*fdf_data;
	float		ortho_size;

	fdf_data = (t_fdf_data*)malloc(sizeof(t_fdf_data));
	fdf_data->mlx_ptr = mlx_init();
	fdf_data->win_ptr = mlx_new_window(fdf_data->mlx_ptr, WIN_W, WIN_H, title);
	fdf_data->f_buf = create_frame_buffer(fdf_data);
	fdf_data->show_info = 1;
	fdf_data->znear = 0.1f;
	fdf_data->zfar = 100.0f;
	fdf_data->aspect = (float)WIN_W / (float)WIN_H;
	fdf_data->ortho_size = map->w;
	ortho_size = fdf_data->ortho_size;
	fdf_data->fov = 35.0f;
	fdf_data->perspective_matrix = create_perspective_matrix(fdf_data->fov,
		fdf_data->aspect, fdf_data->znear, fdf_data->zfar);
	fdf_data->ortho_matrix = create_ortho_matrix(
		ortho_size * fdf_data->aspect, ortho_size, fdf_data->znear,
		fdf_data->zfar);
	fdf_data->m_proj = (t_mat4x4*)malloc(sizeof(t_mat4x4));
	fdf_data->map = map;
	fdf_data->camera.pos = make_vec3_pos(0.0f, 3.0f, map->w);
	ft_set_isometric(fdf_data);
	return (fdf_data);
}

int			del_fdf_data(t_fdf_data *fdf_data)
{
	mlx_destroy_window(fdf_data->mlx_ptr, fdf_data->win_ptr);
	mlx_destroy_image(fdf_data->mlx_ptr, fdf_data->f_buf->img);
	free(fdf_data->m_proj);
	free(fdf_data->map->verts);
	free(fdf_data->map);
	free(fdf_data);
	exit(EXIT_SUCCESS);
	return (1);
}
