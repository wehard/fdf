/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:23:29 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/05 16:32:01 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_W 1280
# define WIN_H 720

# define ESC 53

typedef struct 		s_vec3
{
	int				x;
	int				y;
	int				z;
}					t_vec3;

typedef struct		s_mouse_data
{
	int				x;
	int				y;
	int				oldx;
	int				oldy;
}					t_mouse_data;

typedef struct		s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_mouse_data 	*mouse_data;
}					t_mlx_data;

#endif
