/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 10:19:11 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/08 10:10:13 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "rt.h"
#include "vector.h"

t_geo				*new_cone(t_vec3 position, t_vec3 axis, double angle)
{
	t_cone			*cone;
	t_geo			*geo;

	geo = NULL;
	if (!malloc_geo((void **)(&cone), sizeof(t_cone), 2, &geo))
		return (0);
	vec3_set(position.x, position.y, position.z, geo->origin);
	cone->axis = axis;
	cone->angle = angle * M_PI / 180;
	return (geo);
}

int					belong_to_cone(t_geo *geo, t_vec3 pos)
{
	t_cone			*c;
	t_vec3			diff;
	t_vec3			proj;
	t_vec3			dif;
	t_vec3			oh;

	c = (t_cone*)geo->curr;
	diff = vec3_sub_stack(*geo->origin, pos);
	proj = vec3_add_stack(c->axis, \
		vec3_mult_stack(*geo->origin, vec3_dot(diff, c->axis)));
	dif = vec3_sub_stack(proj, pos);
	oh = vec3_sub_stack(proj, *geo->origin);
	if (vec3_norm(dif) <= tan(c->angle) * vec3_norm(oh) && \
		belong_after_cut(geo, pos))
		return (1);
	return (0);
}

t_hp				hit_cone(t_geo *geo, t_ray *r)
{
	t_hp			sol[2];

	cone_solutions(geo, r, sol);
	if (sol[0].t > 0)
	{
		if (is_geo_dug(geo) && is_cut(geo))
			return (first_in_cut_out_neg(geo, r, sol));
		else if (is_geo_dug(geo))
			return (first_outside_neg(geo, r, sol));
		return (hit_and_cut(geo, sol[0], sol[1], r));
	}
	return (sol[0]);
}
