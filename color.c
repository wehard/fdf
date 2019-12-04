/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:03:59 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/04 18:43:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin

float	ft_convert_range(float oldvalue, float oldmin, float oldmax, float newmin, float newmax)
{
	return ((((oldvalue - oldmin) * (newmax - newmin)) / (oldmax - oldmin)) + newmin);
}

int	ft_color_lerp(int c1, int c2, float t)
{
	return (ft_max(c1, c2) + (ft_max(c1, c2) - ft_min(c1, c2)) * t);
}
