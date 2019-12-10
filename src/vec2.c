/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:21:07 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/10 18:50:20 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec2		make_vec2(float x, float y)
{
	t_vec2 v;

	v.x = 0;
	v.y = 0;
	return (v);
}

t_intvec2	make_intvec2(int x, int y)
{
	t_intvec2 v;

	v.x = x;
	v.y = y;
	return (v);
}
