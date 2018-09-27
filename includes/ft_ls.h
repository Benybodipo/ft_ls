/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 09:19:08 by besteba           #+#    #+#             */
/*   Updated: 2018/09/26 11:53:09 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

typedef struct			s_file_info
{
	int					file_type;
	char				*permissions;
	int					num_links;
	char				*owner;
	char				*group;
	long int			size;
	long int			m_time;
	char				*name;
	char				*path;
	int					xattr;
	blkcnt_t			block_cnt;
	struct s_file_info	*next;
}						t_file_info;

typedef struct			s_options
{
	int					l;
	int					rec;
	int					a;
	int					r;
	int					t;
	char				*path;
}						t_options;

char					*ft_itoa_base(intmax_t num, int base);
void					ft_putchar(int chr);
void					ft_putstr(char *str);
char					*ft_str_append(char *base, char *to_append);
int						ft_strcmp(const char *s1, const char *s2);
size_t					ft_strlen(const char *str);
int						get_int_len(long long num);
char					*padding_left(char *str, int width);
void					print_3params(char *par1, char *par2, char *par3);
char					*char_to_str(int c);

void					capture_input(char *input, t_options *opt);
int						get_file_type(struct stat inf);
void					get_user_group_name(struct stat inf, t_file_info *info);
char					*get_permission(int mode);
int						get_longest_num(t_file_info *head, int index);
blkcnt_t				get_block_cnt(t_file_info *current);
t_file_info				*create(char *d_name, char *path);
void					append(t_file_info **head, char *d_name, char *path);
void					destroy(t_file_info **head);
t_file_info				*ft_lstswap(t_file_info *info1, t_file_info *info2);
void					long_listing(t_file_info *current, int x, int y,
							int xattr);
int						recursion(t_file_info *head, t_options opt);
void					traverse(t_file_info **head, t_options opt);
int						has_xattr(char *path);
int						pad_for_xattr(t_file_info *head);
char					*permissions(int perm);
char					*handle_sticky_b(mode_t mode, char *str);
void					print_format_time(char *str);
void					reset_options(t_options *opt);
void					reset_file_info(t_file_info *info);
char					*handle_permission(char *permission, char *path);
t_file_info				*set_file_info(char *file_name, t_options opt);
t_file_info				*reverse_order(t_file_info *info);
t_file_info				*sort_by_ascii(t_file_info *info);
t_file_info				*sort_by_time(t_file_info *info);
void					sort_list(t_file_info **head, t_options opt);
void					error_handler(int errno, char *name);
void					get_folder_content(char *file_name, char *d_name,
							int opt_a, t_file_info **head);

#endif
