/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:14:55 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/07 11:16:27 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct 		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct 		s_vec2
{
	float			x;
	float			y;
}					t_vec2;

t_vec3	make_vec3(float x, float y, float z);
t_vec2	make_vec2(float x, float y);

#endif
