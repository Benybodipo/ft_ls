/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:46:56 by besteba           #+#    #+#             */
/*   Updated: 2018/09/17 12:49:07 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
