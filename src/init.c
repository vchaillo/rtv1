#include "rtv1.h"

void init_camera(t_env *e)
{
	e->camera.ratio = RATIO;
	e->camera.fov = FOV;
	e->camera.focale = FOCALE;
	e->camera.pos.x = 0;
	e->camera.pos.y = 3;
	e->camera.pos.z = 15;
}

void init_objects(t_env *e)
{
	t_object		objects[4];
	t_material	material_default;
	t_sphere		sphere1;
	t_sphere		sphere2;
	t_plane			plane1;
	t_plane			plane2;
	t_object		object0;
	t_object		object1;
	t_object		object2;
	t_object		object3;

	material_default.type = BASIC;
	material_default.ambient = 0.06;
	material_default.diffuse = 0.9;
	material_default.specular = 1;

	// sphere 1
	sphere1.pos.x = -3;
	sphere1.pos.y = 2;
	sphere1.pos.z = 0;
	sphere1.r = 2;
	object0.type = SPHERE;
	object0.color = new_color(WHITE);
	object0.object = &sphere1;
	object0.material = material_default;
	objects[0] = object0;

	// sphere 2
	sphere2.pos.x = 3;
	sphere2.pos.y = 2;
	sphere2.pos.z = 0;
	sphere2.r = 2;
	object1.type = SPHERE;
	object1.color = new_color(WHITE);
	object1.object = &sphere2;
	object1.material = material_default;
	objects[1] = object1;

	// plane 1
	plane1.norm.vx = 0;
	plane1.norm.vy = 1;
	plane1.norm.vz = 0;
	plane1.d = 0;
	object2.type = PLANE;
	object2.color = new_color(WHITE);
	object2.object = &plane1;
	object2.material = material_default;
	objects[2] = object2;

	// plane 2
	plane2.norm.vx = 0;
	plane2.norm.vy = 1;
	plane2.norm.vz = 0;
	plane2.d = 0;
	object3.type = PLANE;
	object3.color = new_color(WHITE);
	object3.object = &plane2;
	object3.material = material_default;
	objects[3] = object3;

	e->objects = objects;
}

void init_lights(t_env *e)
{
	t_light			lights[4];
	t_light			amb_light;
	t_light			spot_light1;
	t_light			spot_light2;
	t_light			dir_light;

	amb_light.type = AMB;
	amb_light.intensity = 0.1;
	amb_light.color = scalar_color(amb_light.intensity, new_color(WHITE));
	lights[0] = amb_light;

	spot_light1.type = SPOT;
	spot_light1.pos.x = 25;
	spot_light1.pos.y = 20;
	spot_light1.pos.z = 25;
	spot_light1.intensity = 0.5;
	spot_light1.color = scalar_color(spot_light1.intensity, new_color(GREEN));
	lights[1] = spot_light1;

	spot_light2.type = SPOT;
	spot_light2.pos.x = -25;
	spot_light2.pos.y = 20;
	spot_light2.pos.z = 25;
	spot_light2.intensity = 0.5;
	spot_light2.color = scalar_color(spot_light2.intensity, new_color(BLUE));
	lights[2] = spot_light2;

	dir_light.type = DIR;
	dir_light.dir.vx = 1;
	dir_light.dir.vy = 2;
	dir_light.dir.vz = 3;
	dir_light.intensity = 0.5;
	dir_light.color = scalar_color(dir_light.intensity, new_color(YELLOW));

	e->lights = lights;
}


void	init_all(t_env *e)
{
	e->background_color = new_color(BLACK);
	e->nb_rays = 0;



	init_camera(e);
	init_objects(e);
	init_lights(e);
}
