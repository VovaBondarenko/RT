/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurpas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:10:23 by akurpas           #+#    #+#             */
/*   Updated: 2018/05/17 17:10:25 by akurpas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/extra_function.h"

void	vec3_rot(t_vec3 *vector, int xyz, double alfa)
{
	t_vec3 r;

	alfa *= DEG2RAD;
	r = create_vec3(vector->x, vector->y, vector->z);
	if (xyz == X)
	{
		r.y = vector->y * cos(alfa) - vector->z * sin(alfa);
		r.z = vector->y * sin(alfa) + vector->z * cos(alfa);
	}
	else if (xyz == Y)
	{
		r.x = vector->x * cos(alfa) - vector->z * sin(alfa);
		r.z = vector->x * sin(alfa) + vector->z * cos(alfa);
	}
	else if (xyz == Z)
	{
		r.x = vector->x * cos(alfa) - vector->y * sin(alfa);
		r.y = vector->x * sin(alfa) + vector->y * cos(alfa);
	}
	*vector = r;
}
