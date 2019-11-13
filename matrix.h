/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:20:25 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/13 21:47:16 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

#include "point.h"

/*
**	Defines a 4x4 matrix [row][col]
*/

typedef struct	s_mat4x4
{
	float		m[4][4];
}				t_mat4x4;

t_mat4x4	create_identity_matrix(void);
t_mat4x4	create_rotation_matrix_x(float angle);
t_mat4x4	create_rotation_matrix_y(float angle);
t_mat4x4	create_rotation_matrix_z(float angle);
t_mat4x4	create_rotation_matrix_xyz(t_vec3 rad_angle);
t_mat4x4	create_scaling_matrix(t_vec3 scale);
t_mat4x4	create_translation_matrix(t_vec3 translation);
t_mat4x4	create_proj_matrix(float znear, float zfar, float fov, float s_width, float s_height);
t_mat4x4	create_ortho_matrix(float top, float bot, float lft, float rgt, float far, float near);
t_mat4x4	create_model_matrix();
t_mat4x4	create_view_matrix();
t_mat4x4	multiply_matrix(t_mat4x4 a, t_mat4x4 b);
t_vec3		multiply_matrix_vec3(t_vec3 in, t_mat4x4 m);

#endif
