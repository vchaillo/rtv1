#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct  s_point
{
	float         x;
	float         y;
	float         z;
}				        t_point;

typedef struct  s_vector
{
	float         vx;
	float         vy;
	float         vz;
}				        t_vector;

typedef struct	s_sphere
{
	t_point				pos;
  float			    r;
  int				    color;

}			        	t_sphere;

typedef struct	s_plan
{
	t_vector			norm;
  float			    d;
  int				    color;
}			        	t_plan;

// typedef struct	s_object
// {
// 	int						type;
// 	int						material;
// 	t_sphere			sphere;
// 	t_plan				plan;
//   int				    color;
//
// }			        	t_object;

// typedef struct	s_material
// {
// 	int						type;
// 	int				    ambient_color;
// 	int				    diffuse_color;
// 	int				    specular_color;
// }			        	t_material;

typedef struct	s_hitpoint
{
	t_point				pos;
	t_vector			norm;
	int						diffuse_color;
}								t_hitpoint;

typedef struct	s_light
{
	int						type;
	t_point				pos;
	t_vector			dir;
	int						color;
}				        t_light;

typedef struct	s_ray
{
	t_point     	o;
	t_vector     	d;
	float		      t;
	int				   	hit;
	t_hitpoint   	hitpoint;
}				        t_ray;

typedef struct	s_camera
{
	t_point				pos;
	float		  	  ratio;
	float			    fov;
	float			    focale;
}				        t_camera;

typedef struct	s_env
{
  void		      *mlx;
  void		      *win;
  void		      *img;
  char		      *data;
  int			      size;
  int			      endian;
  int           bpp;
  t_camera      camera;
	t_sphere	    sphere;
	t_plan		    plan;
	t_light		    amb;
  t_light		    spot;
  int			      background_color;
  double        nb_rays;
}				        t_env;

#endif
