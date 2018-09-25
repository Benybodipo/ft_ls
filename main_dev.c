/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_dev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 09:18:29 by besteba           #+#    #+#             */
/*   Updated: 2018/09/25 12:12:15 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"
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

void ft_putchar(int chr)
{
	write(1, &chr, 1);
}

void ft_putstr(char *str)
{
	while (*str)
	{
		write(1, &(*str), 1);
		str++;
	}
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

int		ft_strcmp(const char *s1, const char *s2)
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

t_file_info *create(char *d_name, char *path)
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
	info->name = d_name;
	info->path = path;
	info->m_time = inf.st_mtime;
	info->num_links = inf.st_nlink;
	info->size = inf.st_size;
	info->xattr = has_xattr(path);
	info->block_cnt = inf.st_blocks;
	info->next = NULL;
	return (info);
}

void append(t_file_info **Head, char *d_name, char *path)
{
	t_file_info *current;
	t_file_info *new;
	new = create(d_name, path);
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
char *char_to_str(int c)
{
	char *str;

	str = malloc(sizeof(char)*2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void error_handler(int errno, char *name)
{
	char *tmp;

	tmp = name;
	if (errno == 1)
	{
		print_3params("ft_ls: ", tmp, ": No such file or directory\n");
	}
	else if (errno == 2)
	{
		print_3params("ft_ls: illegal option -- ", tmp, "\n");
		ft_putstr("usage: ft_ls [-Ralrt] [file ...]\n");

	}
	else if (errno == 3)
	{
		ft_putstr("Unaccessible file/folder");
	}
	exit(1);
}

void capture_input(char *input, t_options *opt)
{
	int option;

	option = (*input == '-') ? 1 : 0;
	if (!option)
		opt->path = input;
	if (option && !opt->path)
	{
		input++;
		while (*input)
		{
			if (*input == 'l')
				opt->l = 1;
			else if (*input == 'R')
				opt->rec = 1;
			else if (*input == 'a')
				opt->a = 1;
			else if (*input == 'r')
				opt->r = 1;
			else if (*input == 't')
				opt->t = 1;
			else
				error_handler(2, char_to_str(*input));
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
	opt->rec = 0;
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
	info->block_cnt = 0;
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
	else if (S_ISFIFO(inf.st_mode))
		return (112);
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
	if (perm == 4)
		return ("r--");
	else if (perm == 2)
		return ("-w-");
	else if (perm == 6)
		return ("rw-");
	else if (perm == 1)
		return ("--x");
	else if (perm == 5)
		return ("r-x");
	else if (perm == 3)
		return ("-wx");
	else if (perm == 7)
		return ("rwx");
	return ("---");
}

char *handle_sticky_b(mode_t mode, char *str)
{
	int i;
	char *tmp;

	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	if (S_ISUID & mode)
		tmp[2] = tmp[2] == '-' ? 'S' : 's';
	if (S_ISGID & mode)
		tmp[5] = tmp[5] == '-' ? 'S' : 's';
	if (S_ISVTX & mode)
		tmp[8] = tmp[8] == '-' ? 'T' : 't';
	tmp[i] = '\0';
	return (tmp);
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
	str[i] = '\0';
	return (handle_sticky_b(inf.st_mode, str));
}


int get_int_len(long long num)
{
	int len;

	len = 1;
	while (num/=10)
		len++;
	return (len);
}

int get_longest_num(t_file_info *Head, int index)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (Head != NULL)
	{
		i = (index == 1) ? Head->size : Head->num_links;
		len = (len < get_int_len(i)) ? get_int_len(i) : len;
		Head = Head->next;
	}
	return (len);
}

void print_3params(char *par1, char *par2, char *par3)
{
	ft_putstr(par1);
	ft_putstr(par2);
	ft_putstr(par3);
}

void print_format_time(char *str)
{
	char *tmp;
	char format[16];
	int i;

	tmp = str + 4;
	i = 0;
	while (i < 16)
	{
		format[i] = tmp[i];
		i++;
	}
	format[i] = '\0';

	ft_putstr(format);
}
void long_listing(t_file_info *current, int x, int y, int xattr)
{
	char *size;
	char *links;
	char pad;

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

blkcnt_t get_block_cnt(t_file_info *current)
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
	if (info->next && ft_strcmp(info->name, info->next->name) > 0)
		info = ft_lstswap(info, info->next);
	info->next = sort_by_ascii(info->next);
	if (info->next && ft_strcmp(info->name, info->next->name) > 0)
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
/*========================
	- SET INFO
========================*/
t_file_info *set_file_info(char *file_name, t_options opt)
{
	DIR *dir;
	struct dirent *sd;
	t_file_info *Head;
	char *path;
	struct stat buf;

	Head = NULL;
	if (stat(file_name, &buf) == -1)
		error_handler(1, file_name);
	if (S_ISREG(buf.st_mode))
		append(&Head, file_name, file_name);
	else
	{
		dir = opendir(file_name);
		while ((sd = readdir(dir)) != NULL)
		{
			path = ft_str_append(file_name,ft_str_append("/", sd->d_name));
			if (sd->d_name[0] != '.' && !opt.a)
				append(&Head, sd->d_name, path);
			else if ((sd->d_name[0] == '.' || sd->d_name[0] != '.') && opt.a)
				append(&Head, sd->d_name, path);
		}
		if (dir)
			closedir(dir);
	}
	return (Head);
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
	if (opt.l)
		print_3params("total ", ft_itoa_base(get_block_cnt(*Head), 10), "\n");
	while (tmp != NULL)
	{
		sort_list(&tmp, opt);
		cnt = cnt + tmp->block_cnt;
		if (opt.l)
			long_listing(tmp, x, y, pad_for_xattr(*Head));
		else
			print_3params(tmp->name, " ", "\0");
		tmp = tmp->next;
	}
	ft_putstr("\n");
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


int main(int argc, char **argv)
{
	char *input;
	int i;
	t_options opt;
	t_file_info *info;

	reset_options(&opt);
	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			input = argv[i];
			capture_input(input, &opt);
			i++;
		}
		opt.path = (!opt.path) ? "." : opt.path;
		info = set_file_info(opt.path, opt);
	}
	else
		info = set_file_info(".", opt);
	traverse(&info, opt);
	if (opt.rec)
		recursion(info, opt);
	return (0);
}
