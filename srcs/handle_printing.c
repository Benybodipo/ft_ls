/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_printing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:16:10 by besteba           #+#    #+#             */
/*   Updated: 2018/09/17 12:48:27 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void long_listing(t_file_info *current, int x, int y, int xattr)
{
	char *size;
	char *links;
	char pad;

	size = padding_left(ft_itoa_base(current->size, 10), x);
	links = padding_left(ft_itoa_base(current->num_links, 10), y);
	printf("%c", current->file_type);
	printf("%s", handle_permission(current->permissions, current->path));
	if (xattr && current->xattr)
		printf("%c", '@');
	if (xattr && !current->xattr)
		printf("%c", ' ');
	printf(" %s ", links);
	printf("%s ", current->owner);
	printf("%s ", current->group);
	printf("%s ", size);
	printf("%.15s ", (ctime(&current->m_time) + 4));
	printf("%s\n", current->name);
}

int recursion(t_file_info *Head, t_options opt)
{
	t_file_info *current;
	t_file_info *tmp;
	struct stat inf;

	current = Head;
	tmp = NULL;
	while (current)
	{
		if (current->file_type == 'd' && !ft_strcmp(current->name, ".") &&
			!ft_strcmp(current->name, ".."))
		{
			printf("PWD %s:\n", current->path);
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

void traverse(t_file_info **Head, t_options opt)
{
	t_file_info *tmp;
	long long cnt;
	int x;
	int y;

	cnt = 0;
	tmp = *Head;
	x = get_longest_num(*Head, 1);
	y = get_longest_num(*Head, 2);
	printf("total: %lli\n", get_block_cnt(*Head));
	while (tmp != NULL)
	{
		sort_list(&tmp, opt);
		cnt = cnt + tmp->block_cnt;
		long_listing(tmp, x, y, pad_for_xattr(*Head));
		tmp = tmp->next;
	}
}
