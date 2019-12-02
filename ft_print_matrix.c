/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 23:10:19 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/02 21:02:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "matrix.h"

void	ft_print_matrix(t_mat4x4 m, int precision)
{
	int x;
	int y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			printf("%10.*f", precision, m.m[y][x]);
			x++;
		}
		y++;
		printf("\n");
	}
	printf("\n");
}

void	ft_print_vec3(t_vec3 v, int precision)
{
	printf("%5.*f, ", precision, v.x);
	printf("%5.*f, ", precision, v.y);
	printf("%5.*f, ", precision, v.z);
	printf("%5.*f\n", precision, v.w);
}
