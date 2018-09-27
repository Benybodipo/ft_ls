/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 09:35:25 by besteba           #+#    #+#             */
/*   Updated: 2018/09/27 12:27:00 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_handler(int errno, char *name)
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
