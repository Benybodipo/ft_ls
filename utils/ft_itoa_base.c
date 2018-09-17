/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 11:57:59 by besteba           #+#    #+#             */
/*   Updated: 2018/09/17 11:59:05 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
