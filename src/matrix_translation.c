/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:51:43 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 18:22:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4x4	create_translation_matrix(t_vec3 translation)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[3][0] = translation.x;
	mat.m[3][1] = translation.y;
	mat.m[3][2] = translation.z;
	return (mat);
}
