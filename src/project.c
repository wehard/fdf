/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:31:15 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 13:18:25 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3		convert_to_screen_space(t_vec3 p)
{
	p.x += 1.0f;
	p.y += 1.0f;
	p.x *= 0.5f * (float)WIN_W;
	p.y *= 0.5f * (float)WIN_H;
	return (p);
}

t_vec3		ft_transform_point(t_vec3 p, t_mat4x4 mvp)
{
	p = multiply_matrix_vec3(p, mvp);
	p = convert_to_screen_space(p);
	return (p);
}

t_mat4x4	ft_create_mvp(t_fdf_data *fdf_data, t_vec3 p, t_vec3 r, t_vec3 s)
{
	t_mat4x4 m2w;
	t_mat4x4 w2v;
	t_mat4x4 mvp;

	m2w = create_trs_matrix(p, r, s);
	w2v = multiply_matrix(m2w, create_view_matrix(fdf_data->camera.pos));
	mvp = multiply_matrix(w2v, *(fdf_data->m_proj));
	return (mvp);
}

int			ft_discard_point(t_vec3 p)
{
	float zfar = -5.0f;
	float znear = -4.5f;
	if (p.x < -1.0 || p.x > 1.0f)
		return (1);
	if (p.y < -1.0 || p.y > 1.0f)
		return (1);
	//if (p.z < -1.0 || p.z > 1.0)
	//	return (1);
	return (0);
}
