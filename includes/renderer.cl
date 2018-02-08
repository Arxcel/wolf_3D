/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:44:26 by vkozlov           #+#    #+#             */
/*   Updated: 2018/01/24 13:08:21 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

void	get_surface_data(t_ray *ray, t_object object, double t)
{
    if (object.type == O_SPHERE)
        get_sphere_data(ray, object, t);
    else if (object.type == O_CYL)
        get_cyl_data(ray, object, t);
    else if (object.type == O_CON)
        get_con_data(ray, object, t);
    else if (object.type == O_PLANE)
        get_plane_data(ray, object, t);
}

int		check_object_type(t_object object, t_ray *ray, double *t)
{
    if (object.type == O_SPHERE)
        return (sphere_cross(object, ray->orig, ray->dir, t));
    if (object.type == O_CYL)
        return (cyl_cross(object, ray->orig, ray->dir, t));
    if (object.type == O_CON)
        return (con_cross(object, ray->orig, ray->dir, t));
    if (object.type == O_PLANE)
        return (plane_cross(&object, ray, t));
    return (0);
}

static int				ft_trace(	__global t_object *object,
									__global t_light *light,
									__global t_camera *camera,
									double *t_near,
									t_object *hit_object, t_ray *ray)
{
	double	t;
	int		i;
	int		flag;
	int		check;
	double	z_buf;

	i = 0;
	flag = 0;
	z_buf = INF;
	while (object[i].type)
	{
		check = check_object_type(object[i], ray, &t);
		if (check && t < z_buf)
		{
			*t_near = t;
			z_buf = t;
			*hit_object = object[i];
			flag = 1;
		}
		i++;
	}
	return (flag);
}

static t_vector			get_color(	__global t_object *object,
									__global t_light *light,
									__global t_camera *camera,
									t_object h,
									t_ray ray, t_vector hit_color)
{
	double			lt;
	t_vector		col;
	t_ray			light_;
	t_object		shader;
	int				i;

	i = -1;
	while (light[++i].type)
	{
		light_.dir = v_normalize(light[i].pos - ray.p_hit);
		light_.orig = ray.p_hit + v_mult_d(ray.n_hit, camera[0].dias);
		lt = v_dot(ray.n_hit, light_.dir);
		if (!ft_trace(object, light, camera, &shader.p, &shader, &light_))
		{
			col = v_mult_d(h.color, lt + 0.101) + v_mult_d(h.color, 0.101);
			col[0] += (0.8 - h.color[0]) * pow(lt, h.shape) * 0.9;
			col[1] += (0.8 - h.color[1]) * pow(lt, h.shape) * 0.9;
			col[2] += (0.8 - h.color[2]) * pow(lt, h.shape) * 0.9;
		}
		else
			col = v_mult_d(h.color, 0.101);
		hit_color += col;
	}
	return (hit_color);
}

void				find_cam_dir(t_camera *cam, const int i, const int j)
{
	double scale;
	double x;
	double y;

	scale = tan(ft_deg2rad(cam->fov * 0.5));
	x = (2 * (j + 0.5) / (double)IMG_WIDTH - 1) *
		(IMG_WIDTH / (double)WIN_HEIGHT) * scale;
	y = (1 - 2 * (i + 0.5) / (double)WIN_HEIGHT) * scale;
	cam->dir = (t_vector){x, y, -1};
	cam->dir = ft_rotate(cam->dir, cam->rot);
	cam->dir = v_normalize(cam->dir);
}

unsigned int				ft_cast_ray(__global t_object *object,
                                        __global t_light *light,
                                        __global t_camera *camera,
                                        unsigned int hit_color,
                                        t_object *hit_object)
{
    t_ray			ray;
    double			t;
    t_vector		light_;
    
    ray.dir = camera[0].dir;
    ray.orig = camera[0].pos;
    if (ft_trace(object, light, camera, &t, hit_object, &ray))
    {
        get_surface_data(&ray, *hit_object, t);
        light_ = get_color(object, light, camera, *hit_object, ray, (t_vector){0, 0, 0});
        hit_color = set_rgb(light_);
    }
    return (hit_color);
}
