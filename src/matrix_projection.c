/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:53:48 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 18:39:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"

t_mat4x4	create_perspective_matrix(float fov, float ar, float zn, float zf)
{
	t_mat4x4	mat;
	float		tanhalfov;

	tanhalfov = tanf((fov / 2.0f) * M_PI / 180.0f);
	mat.m[0][0] = 1.0f / (tanhalfov * ar);
	mat.m[0][1] = 0.0f;
	mat.m[0][2] = 0.0f;
	mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f;
	mat.m[1][1] = -1.0f / tanhalfov;
	mat.m[1][2] = 0.0f;
	mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f;
	mat.m[2][1] = 0.0f;
	mat.m[2][2] = (-zn - zf) / (zn - zf);
	mat.m[2][3] = (2.0f * zf * zn) / (zn - zf);
	mat.m[3][0] = 0.0f;
	mat.m[3][1] = 0.0f;
	mat.m[3][2] = 1.0f;
	mat.m[3][3] = 0.0f;
	return (mat);
}

t_mat4x4	create_ortho_matrix(float s_w, float s_h, float zn, float zf)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = 2.0f / s_w;
	mat.m[1][1] = 2.0f / -s_h;
	mat.m[2][2] = -2.0f / (zf - zn);
	return (mat);
}
