/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 09:19:08 by besteba           #+#    #+#             */
/*   Updated: 2018/08/27 09:19:10 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_LS_H
#define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

typedef struct s_file_info
{
	int file_type;
	int permissions;
	int num_links;
	char *owner;
	char *group;
	long long size;
	long long data_modif;
	char *path;
} t_file_info;

typedef struct s_options
{
	int l;
	int R;
	int a;
	int r;
	int t;
	char *path;
} t_options;

#endif
