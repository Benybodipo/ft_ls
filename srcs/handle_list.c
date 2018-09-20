/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:04:37 by besteba           #+#    #+#             */
/*   Updated: 2018/09/18 09:44:40 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_file_info		*create(struct dirent *sd, char *path)
{
	t_file_info *info;
	struct stat inf;

	if (!(info = (t_file_info *)malloc(sizeof(t_file_info))))
	{
		printf("Error creating a new node.\n");
		exit(-1);
	}
	stat(path, &inf);
	lstat(path, &inf);
	get_user_group_name(inf, info);
	info->permissions = get_permission(inf.st_mode);
	info->file_type = get_file_type(inf);
	info->name = sd->d_name;
	info->path = path;
	info->m_time = inf.st_mtime;
	info->num_links = inf.st_nlink;
	info->size = inf.st_size;
	info->xattr = has_xattr(path);
	info->block_cnt = inf.st_blocks;
	info->next = NULL;
	return (info);
}

void			append(t_file_info **head, struct dirent *sd, char *path)
{
	t_file_info *current;
	t_file_info *new;

	new = create(sd, path);
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void			destroy(t_file_info **head)
{
	t_file_info *current;
	t_file_info *next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

t_file_info		*ft_lstswap(t_file_info *info1, t_file_info *info2)
{
	info1->next = info2->next;
	info2->next = info1;
	return (info2);
}
