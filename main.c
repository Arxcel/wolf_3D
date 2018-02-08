# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif
# include <stdio.h>
#include <time.h>
#include "my_cl.h"

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
			"__kernel void ft_renderer(                    \n" \
			"   __global t_object          *object,        \n" \
			"   __global t_light           *light,         \n" \
			"   __global t_object          *camera,        \n" \
			"   __global unsigned int      *img_buf        \n" \
			"   )                                          \n" \
			"{                                             \n" \
			" // t_object		hit_object;                \n" \
			"//  t_scene		scene;                     \n" \
			" //  unsigned int z_color;                    \n" \
			"                                              \n" \
			" // scene.object = (t_object*)object;         \n" \
			" // scene.light = (t_light*)light;            \n" \
			" // scene.camera = (t_camera*)camera;         \n" \
			"  //scene.cam_trance = *cam_trance;           \n" \
			"                                              \n" \
			"                                              \n" \
			"   int x = get_global_id(0);                  \n" \
			"   int y = get_global_id(1);                  \n" \
			"   find_cam_dir((t_camera *)camera, x, y);    \n" \
			"   // z_color = ft_cast_ray(object , light, camera, 0, &hit_object);\n" \
			"   *(img_buf + 1280 * y + x) = 50;       \n" \
			"}                                             \n");

	t_cl cl;
	t_args a;
	size_t wd[2] = {5, 5};
	a.number_of_values = 10 * 10;
	a.input_doubles = (double*)malloc(sizeof(double) * 25);
	int i;
	i = -1;
	while (++i < 25)
		a.input_doubles[i] = i + 0.1;
	cl_init(&cl);
	cl_create_program(&cl, "-I ../includes/", text);
	cl_create_kernel(&cl, "ft_renderer");
	cl_create_input_buf(&cl, a, sizeof(a));
	cl_create_res_buf(&cl, (size_t)a.number_of_values);
	cl_set_args(&cl, a.input_doubles,
				(size_t)a.number_of_values * sizeof(double));
	cl_exec_kernel(&cl, 2, wd);
	free(text);
	clock_t stop = clock();
	double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
	printf("\nTime elapsed: %.5f\n", elapsed);
	return (0);
}