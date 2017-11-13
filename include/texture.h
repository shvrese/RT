/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:37:42 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/15 10:55:39 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

#include "rt.h"
#include "vector.h"

void				apply_texture(t_ray *r, t_hp hp, t_geo *geo, t_env *e);

t_color				compute_uv_texture(t_vec2 st);
t_color				checkerboard_texture(t_vec2 st);
t_vec2				planar_mapping(t_hp hp, t_geo *geo);
t_vec2				sphere_mapping(t_hp hp, t_geo *geo);

t_tex				*init_textures(const char *img_path);

#endif
