/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 11:25:17 by besteba           #+#    #+#             */
/*   Updated: 2018/09/27 12:26:44 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

blkcnt_t	get_block_cnt(t_file_info *current)
{
	blkcnt_t cnt;

	cnt = 0;
	while (current != NULL)
	{
		cnt = cnt + current->block_cnt;
		current = current->next;
	}
	return (cnt);
}

void		get_folder_content(char *file_name, char *d_name, int opt_a,
					t_file_info **head)
{
	char *path;

	path = ft_str_append(file_name, ft_str_append("/", d_name));
	if (d_name[0] != '.' && !opt_a)
		append(head, d_name, path);
	else if ((d_name[0] == '.' || d_name[0] != '.') && opt_a)
		append(head, d_name, path);
}
