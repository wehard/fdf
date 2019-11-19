/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:14:55 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/19 12:59:21 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct 		s_vec3
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec3;

typedef struct 		s_vec2
{
	float			x;
	float			y;
}					t_vec2;

typedef struct		s_intvec2
{
	int				x;
	int				y;
}					t_intvec2;

t_vec2				make_vec2(float x, float y);
t_vec3				make_vec3_pos(float x, float y, float z);
t_vec3				make_vec3_rot(float x, float y, float z);
t_vec3				transform_point(t_vec3 v, t_vec3 translate, t_vec3 rot, t_vec3 scale);
t_vec3				translate_point_3d(t_vec3 p, t_vec3 translation);
t_vec3				*make_unit_cube();

#endif
