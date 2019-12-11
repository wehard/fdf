/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:47:57 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 17:50:04 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"

t_mat4x4	create_rotation_matrix_x(float angle)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = 1.0f;
	mat.m[1][1] = cosf(angle);
	mat.m[1][2] = -sinf(angle);
	mat.m[2][1] = sinf(angle);
	mat.m[2][2] = cosf(angle);
	mat.m[3][3] = 1.0f;
	return (mat);
}

t_mat4x4	create_rotation_matrix_y(float angle)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = cosf(angle);
	mat.m[0][2] = -sinf(angle);
	mat.m[1][1] = 1.0f;
	mat.m[2][0] = sinf(angle);
	mat.m[2][2] = cosf(angle);
	return (mat);
}

t_mat4x4	create_rotation_matrix_z(float angle)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = cosf(angle);
	mat.m[0][1] = -sinf(angle);
	mat.m[1][0] = sinf(angle);
	mat.m[1][1] = cosf(angle);
	return (mat);
}

t_mat4x4	create_rotation_matrix_xyz(t_vec3 deg_angle)
{
	t_mat4x4 mat;

	mat = create_rotation_matrix_y(deg_angle.y * (M_PI / 180.0f));
	mat = multiply_matrix(mat,
		create_rotation_matrix_x(deg_angle.x * (M_PI / 180.0f)));
	mat = multiply_matrix(mat,
		create_rotation_matrix_z(deg_angle.z * (M_PI / 180.0f)));
	return (mat);
}
