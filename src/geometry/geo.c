/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:26:59 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/18 17:31:22 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "geo.h"
#include "rt.h"
#include "utils.h"

t_hp				(*g_get_obj_collider(int id))(t_geo *geo, t_ray r)
{
	if (id == 1)
		return (hit_plane);
	if (id == 2)
		return (hit_cone);
	if (id == 3)
		return (hit_cylinder);
	if (id == 4)
		return (hit_sphere);
	if (id == 5)
		return (hit_disk);
	if (id == 6)
		return (hit_pipe);
	return (NULL);
}

static int			setup_geo(t_geo **geo)
{
	*geo = malloc(sizeof(t_geo));
	if (!*geo)
		return (0);
	(*geo)->origin = vec3_new(0, 0, 0);
	if (!(*geo)->origin)
	{
		free(*geo);
		return (0);
	}
	(*geo)->rotation = NULL;
	(*geo)->type = 0;
	(*geo)->curr = NULL;
	(*geo)->mater = malloc(sizeof(t_mater));
	if (!(*geo)->mater)
	{
		free((*geo)->origin);
		free((*geo));
		return (0);
	}
	(*geo)->mater->kd = color_new_stack(0., 0., 0., 0.);
	(*geo)->mater->ks = color_new_stack(0., 0., 0., 0.);
	(*geo)->mater->ior = 1.0;
	(*geo)->is_hit = NULL;
	(*geo)->next = NULL;
	return (1);
}

int					malloc_geo(void **type, int size, int geo_id, t_geo **geo)
{
	if (!setup_geo(geo))
		return (0);
	*type = malloc(size);
	if (!*type)
		return (0);
	(*geo)->curr = *type;
	if (geo_id == 2)
	{
		((t_cone *)*type)->angle = 0;
		((t_cone *)*type)->axis = vec3_stack(0., 0., 0.);
	}
	if (geo_id == 3)
	{
		((t_cylinder *)*type)->radius = 0;
		((t_cylinder *)*type)->axis = vec3_stack(0., 0., 0.);
	}
	if (geo_id == 4)
		((t_sphere *)*type)->radius = 0;
	if (geo_id == 5)
		((t_disk *)*type)->radius = 0;
	if (geo_id == 6)
	{
		((t_pipe *)*type)->radius = 0;
		((t_pipe *)*type)->axis = vec3_stack(0., 0., 0.);
		((t_pipe *)*type)->height = 0;
	}	
	return (1);
}

void				add_geometry(t_geo *geo, t_geo **geos)
{
	t_geo			*tmp;

	if (!*geos)
		*geos = geo;
	else
	{
		tmp = *geos;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = geo;
	}
}
