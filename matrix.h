/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:20:25 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/03 17:06:58 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

#include "point.h"

typedef struct	s_mat4x4
{
	float		m[4][4];
}				t_mat4x4;

t_mat4x4	init_matrix(void);
t_mat4x4	create_identity_matrix(void);
t_mat4x4	create_rotation_matrix_xyz(t_vec3 rad_angle);
t_mat4x4	create_scaling_matrix(t_vec3 scale);
t_mat4x4	create_translation_matrix(t_vec3 translation);

t_mat4x4	create_trs_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale);
t_mat4x4	create_perspective_matrix(float fov, float aspect, float znear, float zfar);
t_mat4x4	create_ortho_matrix(float top, float bot, float lft, float rgt, float znear, float zfar);
t_mat4x4	create_view_matrix(t_vec3 pos);

t_mat4x4	multiply_matrix(t_mat4x4 a, t_mat4x4 b);
t_vec3		multiply_matrix_vec3(t_vec3 in, t_mat4x4 m);
t_vec3		multiply_matrix_vec3_2(t_vec3 in, t_mat4x4 m);

#endif
