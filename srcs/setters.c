/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:42:40 by besteba           #+#    #+#             */
/*   Updated: 2018/09/17 12:49:02 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char *handle_permission(char *permission, char *path)
{
	int i;
	char *perm;
	char *str;
	struct stat inf;

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
	if (S_ISUID & inf.st_mode)
		str[2] = str[2] == '-' ? 'S' : 's';
	if (S_ISGID & inf.st_mode)
		str[2] = str[2] == '-' ? 'S' : 's';
	if (S_ISVTX & inf.st_mode)
		str[8] = str[8] == '-' ? 'T' : 't';
	str[i] = '\0';
	return (str);
}

t_file_info *set_file_info(char *file_name, t_options opt)
{
	DIR *dir;
	struct dirent *sd;
	t_file_info *Head;
	char *path;

	dir = opendir(file_name);
	Head = NULL;
	if (dir == NULL)
	{
		printf("%s\n", "Error! Unable to find the directory");
		exit(1);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		path = ft_str_append(file_name,ft_str_append("/", sd->d_name));
		if (sd->d_name[0] != '.' && !opt.a)
			append(&Head, sd, path);
		else if ((sd->d_name[0] == '.' || sd->d_name[0] != '.') && opt.a)
			append(&Head, sd, path);
	}
	if (dir)
		closedir(dir);
	return (Head);
}
