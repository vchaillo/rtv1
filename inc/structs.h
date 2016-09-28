#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_color
{
	int						r;
	int						g;
	int						b;
}								t_color;

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

typedef struct	s_hitpoint
{
	t_point				pos;
	t_vector			norm;
}								t_hitpoint;

typedef struct	s_ray
{
	t_point     	o;
	t_vector     	d;
	float		      t;
	int				   	hit;
	t_hitpoint   	hitpoint;
}				        t_ray;

typedef struct	s_material
{
	int						type;
	float				  ambient;
	float			    diffuse;
	float			    specular;
}			       		t_material;

typedef struct	s_sphere
{
	t_point				pos;
	float			    r;
}			        	t_sphere;

typedef struct	s_plane
{
	t_vector			norm;
	float			    d;
}			        	t_plane;

typedef struct	s_object
{
	int						type;
	void					*object;
	t_color				color;
	t_material		material;
}				        t_object;

typedef struct	s_light
{
	int						type;
	t_point				pos;
	t_vector			dir;
	float					intensity;
	t_color				color;
}				        t_light;

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
	t_color		    background_color;
  t_camera      camera;
	t_object			*objects;
	t_light				*lights;
	// t_sphere	    sphere;
	// t_sphere	    sphere2;
	// t_plan		    plan;
	// t_plan		    plan2;
	// t_light		    amb;
	// t_light		    spot;
	// t_light		    spot2;
  // t_light		    spot3;
  double        nb_rays;
}				        t_env;

#endif
