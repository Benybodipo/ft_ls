/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 12:07:40 by besteba           #+#    #+#             */
/*   Updated: 2018/09/20 12:08:12 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(int chr)
{
	write(1, &chr, 1);
}