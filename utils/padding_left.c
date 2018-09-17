/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:02:52 by besteba           #+#    #+#             */
/*   Updated: 2018/09/17 12:02:54 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
