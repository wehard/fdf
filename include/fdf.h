/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:23:29 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/13 13:09:12 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>

# define RED ft_make_rgba(1.0f, 0.0f, 0.0f, 1.0f)
# define GREEN ft_make_rgba(0.0f, 1.0f, 0.0f, 1.0f)
# define BLUE ft_make_rgba(0.0f, 0.0f, 1.0f, 1.0f)
# define WHITE ft_make_rgba(1.0f, 1.0f, 1.0f, 1.0f)
# define WIN_W 1280
# define WIN_H 720
# define ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_Z 6
# define KEY_X 7
# define KEY_I 34
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define ISOMETRIC "isometric"
# define PARALLEL "parallel"
# define PERSPECTIVE "perspective"

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec3;

typedef struct		s_vec2
{
	float			x;
	float			y;
}					t_vec2;

typedef struct		s_intvec2
{
	int				x;
	int				y;
}					t_intvec2;

typedef struct		s_rgba
{
	float			r;
	float			g;
	float			b;
	float			a;
}					t_rgba;

typedef struct		s_vertex
{
	t_vec3			pos;
	t_rgba			col;
}					t_vertex;

typedef struct		s_quad
{
	t_vertex		a;
	t_vertex		b;
	t_vertex		c;
	t_vertex		d;
}					t_quad;

typedef struct		s_mat4x4
{
	float			m[4][4];
}					t_mat4x4;

typedef struct		s_v_map
{
	t_vertex		*verts;
	t_vec3			pos;
	t_vec3			rot;
	t_vec3			scale;
	int				size;
	int				w;
	int				h;
	int				h_min;
	int				h_max;
}					t_map;

typedef struct		s_frame_buffer
{
	void			*img;
	char			*d_addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				w;
	int				h;
}					t_frame_buffer;

typedef struct		s_camera
{
	t_vec3			pos;
	t_mat4x4		v_matrix;
}					t_camera;

typedef struct		s_fdf_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_frame_buffer	*f_buf;
	t_mat4x4		*m_proj;
	t_mat4x4		perspective_matrix;
	t_mat4x4		ortho_matrix;
	t_camera		camera;
	t_map			*map;
	float			znear;
	float			zfar;
	float			aspect;
	float			fov;
	float			ortho_size;
	char			*view_state;
	int				show_info;
}					t_fdf_data;

t_fdf_data			*init_fdf_data(char *title, t_map *map);
int					del_fdf_data(t_fdf_data *fdf_data);
int					throw_error(char *e);

void				ft_draw_map(t_fdf_data *fdf_data);
int					read_map_file(int fd, t_map **map, t_rgba c1, t_rgba c2);
t_map				*create_map(int w, int h);
void				calculate_map_minmax(t_map *map);

void				frame_buffer_set(t_frame_buffer *fb, int x, int y, int c);
void				clear_frame_buffer(t_frame_buffer *fb);
t_frame_buffer		*create_frame_buffer(t_fdf_data *fdf_data);

void				ft_set_parallel(t_fdf_data *fdf_data);
void				ft_set_isometric(t_fdf_data *fdf_data);
void				ft_set_perspective(t_fdf_data *fdf_data);
int					on_key_down(int key, void *param);

void				draw_line(t_frame_buffer *fb, t_vertex p0, t_vertex p1);
t_vec3				convert_to_screen_space(t_vec3 p);
t_vec3				ft_transform_point(t_vec3 p, t_mat4x4 mvp);
t_mat4x4			ft_create_mvp(t_fdf_data *fdf_data,
									t_vec3 p, t_vec3 r, t_vec3 s);
int					ft_discard_point(t_vec3 p);

t_mat4x4			init_matrix(void);
t_mat4x4			create_identity_matrix(void);
t_mat4x4			create_rotation_matrix_xyz(t_vec3 deg_angle);
t_mat4x4			create_scaling_matrix(t_vec3 scale);
t_mat4x4			create_translation_matrix(t_vec3 translation);
t_mat4x4			create_trs_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale);
t_mat4x4			create_perspective_matrix(
								float fov, float ar, float zn, float zf);
t_mat4x4			create_ortho_matrix(
								float s_w, float s_h, float zn, float zf);
t_mat4x4			create_view_matrix(t_vec3 pos);
t_mat4x4			multiply_matrix(t_mat4x4 a, t_mat4x4 b);
t_vec3				multiply_matrix_vec3(t_vec3 in, t_mat4x4 m);

t_vertex			make_vertex(float x, float y, float z, t_rgba c);
t_vec2				make_vec2(float x, float y);
t_intvec2			make_intvec2(int x, int y);
t_intvec2			set_intvec2(int x, int y);
t_vec3				make_vec3_pos(float x, float y, float z);
t_vec3				make_vec3_rot(float x, float y, float z);
t_vec3				add_vec3(t_vec3 a, t_vec3 b);

float				ft_inverse_lerp(float value, float a, float b);
float				ft_lerp_f(float n1, float n2, float t);
t_rgba				ft_make_rgba(float r, float g, float b, float a);
t_rgba				ft_lerp_rgba(t_rgba c1, t_rgba c2, float t);
int					ft_get_color(t_rgba c);

void				ft_draw_axis(t_fdf_data *fdf_data, t_vec3 p, t_vec3 r,
								float s);
void				ft_draw_info(t_fdf_data *fdf_data);

#endif
