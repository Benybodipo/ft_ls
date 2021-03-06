/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 11:59:33 by besteba           #+#    #+#             */
/*   Updated: 2018/09/27 12:28:17 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
