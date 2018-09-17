/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:10:21 by besteba           #+#    #+#             */
/*   Updated: 2018/09/17 12:49:22 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_file_info *reverse_order(t_file_info *info)
{
	t_file_info *x;
	t_file_info *y;
	t_file_info *z;

	x = NULL;
	y = info;
	z = info->next;
	while (y)
	{
		z = y->next;
		y->next = x;
		x = y;
		y = z;
	}
	return (x);
}

t_file_info *sort_by_ascii(t_file_info *info)
{
	if (!info)
		return (NULL);
	if (info->next && ft_strcmp2(info->name, info->next->name) > 0)
		info = ft_lstswap(info, info->next);
	info->next = sort_by_ascii(info->next);
	if (info->next && ft_strcmp2(info->name, info->next->name) > 0)
	{
		info = ft_lstswap(info, info->next);
		info->next = sort_by_ascii(info->next);
	}
	return (info);
}

t_file_info *sort_by_time(t_file_info *info)
{
	if (!info)
		return (0);
	if (info->next && (info->m_time < info->next->m_time))
		info = ft_lstswap(info, info->next);
	info->next = sort_by_time(info->next);
	if (info->next && (info->m_time < info->next->m_time))
	{
		info = ft_lstswap(info, info->next);
		info->next = sort_by_time(info->next);
	}
	return (info);
}

void sort_list(t_file_info **Head, t_options opt)
{
	*Head = sort_by_ascii(*Head);
	if (opt.t)
		*Head = sort_by_time(*Head);
	if (opt.r)
		*Head = reverse_order(*Head);
}
