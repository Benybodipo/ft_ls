/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:33:29 by besteba           #+#    #+#             */
/*   Updated: 2018/09/25 11:54:53 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	capture_input(char *input, t_options *opt)
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

int		get_file_type(struct stat inf)
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

void	get_user_group_name(struct stat inf, t_file_info *info)
{
	struct passwd	*pwd;
	struct group	*group;

	pwd = getpwuid(inf.st_uid);
	group = getgrgid(inf.st_gid);
	info->owner = pwd->pw_name;
	info->group = group->gr_name;
}

char	*get_permission(int mode)
{
	char	*num;
	int		i;

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

int		get_longest_num(t_file_info *head, int index)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (head != NULL)
	{
		i = (index == 1) ? head->size : head->num_links;
		len = (len < get_int_len(i)) ? get_int_len(i) : len;
		head = head->next;
	}
	return (len);
}

blkcnt_t	get_block_cnt(t_file_info *current)
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
