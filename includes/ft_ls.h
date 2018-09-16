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
#include <sys/xattr.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

typedef struct s_file_info
{
	int file_type;
	char *permissions;
	int num_links;
	char *owner;
	char *group;
	long int size;
	long int m_time;
	char *name;
	char *path;
	int xattr;
	blkcnt_t block_cnt;
	struct s_file_info *next;
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

typedef struct s_folder_path
{
	char *path;
	struct s_folder_path *next;
} t_folder_path;

int get_file_type(struct stat inf);
void get_user_group_name(struct stat inf, t_file_info *info);
char  *get_permission(int mode);

#endif
