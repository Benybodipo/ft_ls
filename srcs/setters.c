/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:42:40 by besteba           #+#    #+#             */
/*   Updated: 2018/09/27 12:27:32 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*handle_permission(char *permission, char *path)
{
	int				i;
	char			*perm;
	char			*str;
	struct stat		inf;

	stat(path, &inf);
	if (!(str = (char *)malloc(sizeof(char) * 12)))
		return (NULL);
	i = 0;
	while (*permission)
	{
		perm = permissions(*permission - '0');
		while (*perm)
		{
			str[i] = *perm;
			i++;
			perm++;
		}
		permission++;
	}
	str[i] = '\0';
	return (handle_sticky_b(inf.st_mode, str));
}

t_file_info		*set_file_info(char *file_name, t_options opt)
{
	DIR				*dir;
	struct dirent	*sd;
	t_file_info		*head;
	struct stat		buf;

	head = NULL;
	if (stat(file_name, &buf) == -1)
		error_handler(1, file_name);
	if (S_ISREG(buf.st_mode))
		append(&head, file_name, file_name);
	else
	{
		dir = opendir(file_name);
		while ((sd = readdir(dir)) != NULL)
			get_folder_content(file_name, sd->d_name, opt.a, &head);
		if (dir)
			closedir(dir);
	}
	return (head);
}
