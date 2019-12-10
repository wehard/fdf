/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:23:29 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/10 18:54:23 by wkorande         ###   ########.fr       */
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
# define SPACE 49
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_R 15
# define KEY_F 3
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

typedef struct 		s_rgba
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

typedef struct	s_mat4x4
{
	float		m[4][4];
}				t_mat4x4;

typedef struct 		s_line
{
	t_vec3			p0;
	t_vec3			p1;
	int				color;
}					t_line;

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

typedef struct		s_depth_buffer
{
	float			*data;
	int				width;
	int				height;
}					t_depth_buffer;

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
	t_depth_buffer	*db;
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

t_fdf_data		*init_fdf_data(char *title, t_map *map);
int				del_fdf_data(t_fdf_data *fdf_data);

int				read_map_file(int fd, t_map **map, t_rgba low, t_rgba high);

void			frame_buffer_set(t_frame_buffer *fb, int x, int y, int color);
void			clear_frame_buffer(t_frame_buffer *fb);
t_frame_buffer	*create_frame_buffer(t_fdf_data *fdf_data);

void			depth_buffer_set(t_depth_buffer *db, int x, int y, float f);
t_depth_buffer	*create_depth_buffer(int width, int height);
void			clear_depth_buffer(t_depth_buffer *db, float value);
float			depth_buffer_sample(t_depth_buffer *db, int x, int y);

void			ft_set_parallel(t_fdf_data *fdf_data);
void			ft_set_isometric(t_fdf_data *fdf_data);
void			ft_set_perspective(t_fdf_data *fdf_data);

void			draw_line(t_frame_buffer *fb, t_depth_buffer *db, t_vertex p0, t_vertex p1);

t_vec3 			convert_to_screen_space(t_vec3 p);

int				throw_error(char *e);

int				on_key_down(int key, void *param);
int				mouse_event(int button, int x, int y, void *param);

void			ft_print_matrix(t_mat4x4 m, int precision);
void			ft_print_vec3(t_vec3 v, int precision);

int				ft_color_lerp(int c1, int c2, float t);
float			ft_convert_range(float oldvalue, float oldmin, float oldmax, float newmin, float newmax);

float			ft_lerp_f(float n1, float n2, float t);
t_rgba 			ft_make_rgba(float r, float g, float b, float a);
t_rgba			ft_lerp_rgba(t_rgba c1, t_rgba c2, float t);
int				ft_get_color(t_rgba c);

t_vertex		make_vertex(float x, float y, float z, t_rgba c);

t_vec2			make_vec2(float x, float y);
t_intvec2		make_intvec2(int x, int y);
t_vec3			make_vec3_pos(float x, float y, float z);
t_vec3			make_vec3_rot(float x, float y, float z);
t_vec3			add_vec3(t_vec3 a, t_vec3 b);

t_mat4x4		init_matrix(void);
t_mat4x4		create_identity_matrix(void);
t_mat4x4		create_rotation_matrix_xyz(t_vec3 deg_angle);
t_mat4x4		create_scaling_matrix(t_vec3 scale);
t_mat4x4		create_translation_matrix(t_vec3 translation);

t_mat4x4		create_trs_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale);
t_mat4x4		create_perspective_matrix(float fov, float aspect, float znear, float zfar);
t_mat4x4		create_ortho_matrix(float top, float bot, float lft, float rgt, float znear, float zfar);
t_mat4x4		create_view_matrix(t_vec3 pos);

t_mat4x4		multiply_matrix(t_mat4x4 a, t_mat4x4 b);
t_vec3			multiply_matrix_vec3(t_vec3 in, t_mat4x4 m);
t_vec3			multiply_matrix_vec3_2(t_vec3 in, t_mat4x4 m);

#endif
