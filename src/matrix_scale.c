/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:52:34 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 17:52:47 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4x4	create_scaling_matrix(t_vec3 scale)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = scale.x;
	mat.m[1][1] = scale.y;
	mat.m[2][2] = scale.z;
	return (mat);
}
