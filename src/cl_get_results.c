/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get_results.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:48:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/09 12:48:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cl.h"

unsigned int  *cl_get_res(t_cl *cl, size_t size)
{
	unsigned int *l_result;
	cl_event    readResultsEvent;

	l_result = (unsigned int*)malloc(sizeof(unsigned int) * size);
	clEnqueueReadBuffer(cl->commands, cl->output_buf, CL_TRUE,
						0, size, l_result, 0,
						NULL, &readResultsEvent);
	return l_result;
}