/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_printing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:16:10 by besteba           #+#    #+#             */
/*   Updated: 2018/09/27 12:27:10 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	long_listing(t_file_info *current, int x, int y, int xattr)
{
	char	*size;
	char	*links;

	size = padding_left(ft_itoa_base(current->size, 10), x);
	links = padding_left(ft_itoa_base(current->num_links, 10), y);
	ft_putchar(current->file_type);
	ft_putstr(handle_permission(current->permissions, current->path));
	if (xattr && current->xattr)
		ft_putchar('@');
	if (xattr && !current->xattr)
		ft_putchar(' ');
	print_3params(" ", links, " ");
	print_3params(current->owner, " ", "\0");
	print_3params(current->group, " ", "\0");
	print_3params(size, " ", "\0");
	print_format_time(ctime(&current->m_time));
	print_3params(current->name, "\n", "\0");
}

int		recursion(t_file_info *head, t_options opt)
{
	t_file_info *current;
	t_file_info *tmp;

	current = head;
	tmp = NULL;
	while (current)
	{
		if (current->file_type == 'd' && ft_strcmp(current->name, ".") &&
			ft_strcmp(current->name, ".."))
		{
			ft_putstr(current->path);
			ft_putstr(": \n");
			tmp = set_file_info(current->path, opt);
			if (tmp)
			{
				traverse(&tmp, opt);
				recursion(tmp, opt);
			}
		}
		current = current->next;
	}
	return (1);
}

void	traverse(t_file_info **head, t_options opt)
{
	t_file_info	*tmp;
	long long	cnt;
	int			x;
	int			y;

	cnt = 0;
	tmp = *head;
	x = get_longest_num(*head, 1);
	y = get_longest_num(*head, 2);
	if (opt.l)
		print_3params("total ", ft_itoa_base(get_block_cnt(*head), 10), "\n");
	while (tmp != NULL)
	{
		sort_list(&tmp, opt);
		cnt = cnt + tmp->block_cnt;
		if (opt.l)
			long_listing(tmp, x, y, pad_for_xattr(*head));
		else
			print_3params(tmp->name, "\n", "\0");
		tmp = tmp->next;
	}
	ft_putstr("\n");
}
