/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:46:56 by besteba           #+#    #+#             */
/*   Updated: 2018/09/27 12:27:15 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		has_xattr(char *path)
{
	int boolean;

	boolean = (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0) ? 1 : 0;
	return (boolean);
}

int		pad_for_xattr(t_file_info *head)
{
	while (head)
	{
		if (head->xattr)
			return (1);
		head = head->next;
	}
	return (0);
}

char	*permissions(int perm)
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

char	*handle_sticky_b(mode_t mode, char *str)
{
	int		i;
	char	*tmp;

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

void	print_format_time(char *str)
{
	char	*tmp;
	char	format[16];
	int		i;

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
