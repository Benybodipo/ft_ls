/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resetters.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:27:36 by besteba           #+#    #+#             */
/*   Updated: 2018/09/27 12:27:25 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reset_options(t_options *opt)
{
	opt->l = 0;
	opt->rec = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->path = NULL;
}

void	reset_file_info(t_file_info *info)
{
	info->file_type = 0;
	info->permissions = NULL;
	info->num_links = 0;
	info->owner = NULL;
	info->group = NULL;
	info->size = 0;
	info->m_time = 0;
	info->name = NULL;
	info->path = NULL;
	info->xattr = 0;
	info->block_cnt = 0;
}
