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
int has_xattr(char *path);

/*========================
	- UTILS -
========================*/
size_t	ft_strlen(const char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char		*ft_str_append(char *base, char *to_append)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(base) + ft_strlen(to_append);
	new = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (*base)
	{
		new[i] = *base;
		i++;
		base++;
	}
	while (*to_append)
	{
		new[i] = *to_append;
		to_append++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

int ft_strcmp(char *str1, char *str2)
{
	if (ft_strlen(str1) == ft_strlen(str2))
	{
		while (*str2 == *str2 && *str1 && *str2)
		{
			str1++;
			str2++;
		}
		if (!*str1 && !*str2)
			return (1);
	}
	return (0);
}

int		ft_strcmp2(const char *s1, const char *s2)
{
	unsigned	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_itoa_base(intmax_t num, int base)
{
	int			len;
	char		*str;
	intmax_t	value;
	char		*tab;

	tab = "0123456789abcdef";
	value = num;
	len = (value < 0 && base == 10) ? 1 : 0;
	value = (value < 0) ? (-1 * value) : value;
	while (value /= base)
		len++;
	value = num;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (value < 0 && base == 10)
		str[0] = '-';
	value = (value < 0) ? value * -1 : value;
	if (value == 0)
		return ("0");
	while (value > 0)
	{
		str[len] = tab[value % base];
		value /= base;
		len--;
	}
	return (str);
}

char		*padding_left(char *str, int width)
{
	int		i;
	char	*new;

	i = 0;
	if (width <= ft_strlen(str))
		return (str);
	new = malloc(sizeof(char) * (width + 1));
	while (i < width - ft_strlen(str))
	{
		new[i] = ' ';
		i++;
	}
	while (i < width && *str)
	{
		new[i] = *str;
		i++;
		str++;
	}
	new[i] = '\0';
	return (new);
}
/*========================
	- LINKED LISTS
========================*/

t_folder_path *create_path(char *path)
{
	t_folder_path *pth;
	if (!(pth = (t_folder_path *)malloc(sizeof(t_folder_path))))
	{
		printf("Error creating a new node.\n");
		exit(-1);
	}
	pth->path = path;
	pth->next = NULL;
	return (pth);
}

t_file_info *create(struct dirent *sd, char *path)
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
	info->next = NULL;
	return (info);
}

void append(t_file_info **Head, struct dirent *sd, char *path)
{
	t_file_info *current;
	t_file_info *new;
	new = create(sd, path);
	if (*Head == NULL)
		*Head = new;
	else
	{
		current = *Head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void append_path(t_folder_path **Head, char *path)
{
	t_folder_path *current;
	t_folder_path *new;

	new = create_path(path);
	if (*Head == NULL)
		*Head = new;
	else
	{
		current = *Head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void destroy(t_file_info **Head)
{
    t_file_info *current = *Head;
    t_file_info *next;

    while (current != NULL)
    {
       next = current->next;
       free(current);
       current = next;
    }
    *Head = NULL;
}

t_file_info		*ft_lstswap(t_file_info *info1, t_file_info *info2)
{
	info1->next = info2->next;
	info2->next = info1;
	return (info2);
}
/*========================
	- GETTERS
========================*/


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

int has_xattr(char *path)
{
	int boolean = (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0) ? 1 : 0;
	return (boolean);
}

int pad_for_xattr(t_file_info *Head)
{
	while (Head)
	{
		if (Head->xattr)
			return (1);
		Head = Head->next;
	}
	return (0);
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

void reset_file_info(t_file_info *info)
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
}

int get_file_type(struct stat inf)
{
	if (S_ISREG(inf.st_mode))
		return (45);
	else if (S_ISDIR(inf.st_mode))
		return (100);
	else if (S_ISLNK(inf.st_mode))
		return (108);
	else if (S_ISBLK(inf.st_mode))
		return (98);
	else if (S_ISCHR(inf.st_mode))
		return (99);
	// else if (S_ISIFO(inf.st_mode))
	// 	return (112);
	else if (S_ISSOCK(inf.st_mode))
		return (115);
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
char *permissions(int perm)
{
	if (perm == 1)
		return ("r--");
	else if (perm == 2)
		return ("-w-");
	else if (perm == 3)
		return ("rw-");
	else if (perm == 4)
		return ("--x");
	else if (perm == 5)
		return ("r-x");
	else if (perm == 6)
		return ("-wx");
	else if (perm == 7)
		return ("rwx");
	return ("---");
}


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
	// if (S_ISUID & inf.st_mode)
	// 	str[2] = str[2] == '-' ? 'S' : 's';
	// if (S_ISGID & inf.st_mode)
	// 	str[2] = str[2] == '-' ? 'S' : 's';
	// if (S_ISVTX & inf.st_mode)
	// 	str[8] = str[8] == '-' ? 'T' : 't';
	str[i] = '\0';
	return (str);
}


int get_int_len(long long num)
{
	int len;

	len = 1;
	while (num/=10)
		len++;
	return (len);
}

int get_longest_num(t_file_info *Head)
{
	int len;

	len = 0;
	while (Head != NULL)
	{
		len = (len < get_int_len(Head->size)) ? get_int_len(Head->size) : len;
		Head = Head->next;
	}
	return (len);
}


void long_listing(t_file_info *current, int len, int xattr)
{
	char *size;
	char pad;

	size = padding_left(ft_itoa_base(current->size, 10), len);
	printf("%c", current->file_type);
	printf("%s", handle_permission(current->permissions, current->path));
	if (xattr && current->xattr)
		printf("%c ", '@');
	if (xattr && !current->xattr)
		printf("%c ", ' ');
	printf("%i ", current->num_links);
	printf("%s ", current->owner);
	printf("%s ", current->group);
	printf("%s ", size);
	printf("%.15s ", (ctime(&current->m_time) + 4));
	printf("%s\n", current->name);
}

void traverse(t_file_info **Head, t_options opt)
{
	t_file_info *tmp = *Head;
	t_file_info *tmp2 = tmp;
	int len = 0;

	while (tmp != NULL)
	{
		long_listing(tmp, get_longest_num(*Head), pad_for_xattr(*Head));
		tmp = tmp->next;
	}
}

/*========================
	- SORT LIST
========================*/
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

// t_file_info *sort_by_size(t_file_info *info)
// {
// 	if (!info)
// 		return (0);
// 	if (info->next && (info->size < info->next->size))
// 		info = ft_lstswap(info, info->next);
// 	info->next = sort_by_size(info->next);
// 	if (info->next && (info->size < info->next->size))
// 	{
// 		info = ft_lstswap(info, info->next);
// 		info->next = sort_by_size(info->next);
// 	}
// 	return (info);
// }

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

int sort_list(t_file_info **Head, t_options opt)
{
	*Head = sort_by_ascii(*Head);
	if (opt.t)
		*Head = sort_by_time(*Head);
	if (opt.r)
		*Head = reverse_order(*Head);
}
/*========================
	- SET INFO
========================*/
t_file_info *set_file_info(char *file_name)
{
	DIR *dir;
	struct dirent *sd;
	struct stat inf;
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
		if (!ft_strcmp(sd->d_name, ".") && !ft_strcmp(sd->d_name, "..") && sd->d_name[0] != '.')
			append(&Head, sd, path);
	}
	if (dir)
		closedir(dir);
	return (Head);
}

/*========================
	- RECURSION
========================*/
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
			tmp = set_file_info(current->path);
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


int main(int argc, char **argv)
{
	char *input;
	int i;
	t_options opt;
	t_file_info *info;

	if (argc > 1)
	{
		reset_options(&opt);
		i = 1;
		while (argv[i])
		{
			input = argv[i];
			capture_input(input, &opt);
			info = set_file_info(opt.path);
			traverse(&info, opt);

			printf("=== %s ===\n", "sort_by_time");
			t_file_info *time = sort_by_time(info);
			traverse(&time, opt);
			i++;
		}
	}
	return (0);
}
