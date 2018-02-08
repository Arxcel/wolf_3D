# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif
# include <stdio.h>
#include <time.h>
#include "my_cl.h"
#include "../includes/ft_rtv1.h"

int					main(void) {
	clock_t start = clock();
	char *text;
	text = ft_strdup("\n" \
			"#include \"ft_rtv1.h\"                        \n" \
			"#include \"conus.cl\"                         \n" \
			"#include \"cylinder.cl\"                      \n" \
			"#include \"ft_matrix.cl\"                     \n" \
			"#include \"ft_vector.cl\"                     \n" \
			"#include \"renderer.cl\"                      \n" \
			"#include \"rotation.cl\"                      \n" \
			"#include \"sphere.cl\"                        \n" \
			"#include \"utils.cl\"                         \n" \
			"                                              \n" \
			"__kernel void kernel_exec(                    \n" \
			"   __global t_object          *object,        \n" \
			"   __global t_light           *light,         \n" \
			"   __global t_camera          *camera,        \n" \
			"   __global unsigned int      *img_buf        \n" \
			"   )                                          \n" \
			"{                                             \n" \
			" // t_object		hit_object;                \n" \
			"  t_scene		scene;                         \n" \
			" //  unsigned int z_color;                    \n" \
			"                                              \n" \
			"  scene.object = (t_object*)object;           \n" \
			"  scene.light = (t_light*)light;              \n" \
			"  scene.camera = (t_camera*)camera;           \n" \
			"                                              \n" \
			"                                              \n" \
			"                                              \n" \
			"   int x = get_global_id(0);                  \n" \
			"   int y = get_global_id(1);                  \n" \
			"   ft_renderer(object, light, camera, x, y);  \n" \
			"   // printf(\"x: %d\ty: %d\\n\", x, y);      \n" \
			"   // printf(\"object[0].type: %d\\n\", object[0].type); \n" \
			"   //find_cam_dir((t_camera *)camera, x, y);    \n" \
			"   // z_color = ft_cast_ray(object , light, camera, 0, &hit_object);\n" \
			"  // *(img_buf + 1280 * y + x) = 50;       \n" \
			"}                                             \n");

	t_cl cl;
	size_t wd[2] = {5, 5};
	t_scene s;
	unsigned int img[WIN_WIDTH * WIN_HEIGHT];

	if (!(s.object = (t_object*)ft_memalloc(sizeof(t_object) * 2)))
	{
		ft_printf("Error allocating memory");
		exit(1);
	}
	s.object[0].type = O_SPHERE;
	s.object[0].point = (t_vector){0, 0, -300};
	s.object[0].radius = 100;
	s.object[0].color = (t_vector){85 / 255 , 5 / 255, 5 / 255};
	s.object[0].shape = 100;
	s.object[1].type = 0;
	if (!(s.camera = (t_camera*)ft_memalloc(sizeof(t_camera) * 2)))
	{
		ft_printf("Error allocating memory");
		exit(1);
	}
	s.camera[0].type = 1;
	s.camera[0].pos = (t_vector){0, 0, 0};
	s.camera[0].fov = 50;
	s.camera[0].dias = 0.3;
	s.camera[0].rot = (t_vector){0, 0, 0};
	s.camera[1].type = 0;
	if (!(s.light = (t_light *)ft_memalloc(sizeof(t_light) * 2)))
	{
		ft_printf("Error allocating memory");
		exit(1);
	}
	s.light[0].type = L_SUN;
	s.light[0].pos = (t_vector){500, 0, 500};
	s.light[0].color = (t_vector){1, 1, 1};
	s.light[1].type = 0;

	cl_init(&cl);
	cl_create_program(&cl, "-I ../includes/", text);
	cl_create_kernel(&cl, "kernel_exec");
	//cl_create_input_buf(&cl, a, sizeof(a));
	cl_create_res_buf(&cl, (size_t)(size_t)WIN_WIDTH * WIN_HEIGHT * sizeof(unsigned int));
	cl_set_args(&cl, s.object, 2, 0);
	cl_set_args(&cl, s.light, 2, 1);
	cl_set_args(&cl, s.camera, 2, 2);
	cl_set_args(&cl, img, (size_t)WIN_WIDTH * WIN_HEIGHT, 3);
	cl_exec_kernel(&cl, 2, wd);
	free(text);
	clock_t stop = clock();
	double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
	printf("\nTime elapsed: %.5f\n", elapsed);
	return (0);
}