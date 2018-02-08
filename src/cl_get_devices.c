/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get_devices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:38:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/07 17:38:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cl.h"

void	cl_get_devices(t_cl *cl)
{
	cl_uint		max_devices;
	cl_uint		num_devices;
	cl_int		res;

	max_devices = 1;
	cl->devices = (cl_device_id*)malloc(max_devices * sizeof(cl_device_id));
	res = clGetDeviceIDs(cl->platforms[0], CL_DEVICE_TYPE_GPU, max_devices,
						cl->devices, &num_devices);
	if(res != CL_SUCCESS)
	{
		res = clGetDeviceIDs(cl->platforms[0], CL_DEVICE_TYPE_CPU, max_devices,
							cl->devices, &num_devices);
		if(res != CL_SUCCESS)
		{
			ft_printf("Error while getting devices. Code:[%d]\n", res);
			exit(1);
		}
	}
	clGetDeviceInfo(cl->devices[0], CL_DEVICE_NAME, 128, cl->device_name, NULL);
}