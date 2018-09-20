/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:42:40 by besteba           #+#    #+#             */
/*   Updated: 2018/09/18 12:50:06 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char			*path;

	dir = opendir(file_name);
	head = NULL;
	if (dir == NULL)
	{
		printf("%s\n", "Error! Unable to find the directory");
		exit(1);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		path = ft_str_append(file_name, ft_str_append("/", sd->d_name));
		if (sd->d_name[0] != '.' && !opt.a)
			append(&head, sd, path);
		else if ((sd->d_name[0] == '.' || sd->d_name[0] != '.') && opt.a)
			append(&head, sd, path);
	}
	if (dir)
		closedir(dir);
	return (head);
}
