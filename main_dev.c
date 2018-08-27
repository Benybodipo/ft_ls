/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_dev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 09:18:29 by besteba           #+#    #+#             */
/*   Updated: 2018/08/27 09:18:31 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/ft_ls.h"

char			*ft_itoa_base(int num, int base)
{
	int			len;
	char		*str;
	long long	value;
	char		*tab;

	tab = "0123456789abcdef";
	value = num;
	len = (value < 0 && base == 10) ? 1 : 0;
	value = (value < 0) ? (-1 * value) : value;
	while (value /= base)
		len++;
	value = num;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (value < 0 && base == 10)
		str[0] = '-';
	if (value < 0)
		value = value * -1;
	while (value > 0)
	{
		str[len] = tab[value % base];
		value /= base;
		len--;
	}
	return (str);
}

void capture_input(char *input, t_options *opt)
{
	int option;

	option = (*input == '-') ? 1 : 0;
	if (!option)
		opt->path = input;
	else
	{
		input++;
		while (*input)
		{
			if (*input == 'l')
				opt->l = 1;
			else if (*input == 'R')
				opt->R = 1;
			else if (*input == 'a')
				opt->a = 1;
			else if (*input == 'r')
				opt->r = 1;
			else if (*input == 't')
				opt->t = 1;
			input++;
		}
	}
}

void reset_options(t_options *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->path = NULL;
}

int get_file_type(struct stat inf)
{
	if (S_ISREG(inf.st_mode))
		return (1);
	else if (S_ISDIR(inf.st_mode))
		return (2);
	else if (S_ISLNK(inf.st_mode))
		return (3);
	return (0);
}
void get_user_group_name(struct stat inf, t_file_info *info)
{
	struct passwd *pwd;
	struct group *group;

	pwd = getpwuid(inf.st_uid);
	group =  getgrgid(inf.st_gid);
	info->owner = pwd->pw_name;
	info->group = group->gr_name;
}

char  *get_permission(int mode)
{
	char *num;
	int  i;

	num = ft_itoa_base(mode, 8);
	i = 0;
	while (*num)
		num++;
	while (num && i < 3)
	{
		num--;
		i++;
	}
	return (num);
}
void set_file_info(char *file_name, t_file_info *info)
{
	DIR *dir;
	struct dirent *sd;
	struct stat inf;

	dir = opendir(file_name);
	if (dir == NULL)
	{
		printf("%s\n", "Error! Unable to find the directory");
		exit(1);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		stat(sd->d_name, &inf);
		lstat(sd->d_name, &inf);
		get_user_group_name(inf, info);
		info->permissions = get_permission(inf.st_mode);
		info->file_type = get_file_type(inf);
		info->path = sd->d_name;
		info->c_time = inf.st_ctime;
		info->num_links = inf.st_nlink;
		info->size = inf.st_size;
	}
}
int main(int argc, char **argv)
{
	char *input;
	int i;
	t_options opt;
	t_file_info info;

	if (argc > 1)
	{
		reset_options(&opt);
		i = 1;
		while (argv[i])
		{
			input = argv[i];
			capture_input(input, &opt);
			set_file_info(opt.path, &info);
			i++;
		}
	}

	return (0);
}
