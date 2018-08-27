/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_dev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 09:18:29 by besteba           #+#    #+#             */
/*   Updated: 2018/08/27 09:18:31 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/ft_ls.h"

void capture_input(char *input, t_options *opt)
{
	int option;

	option = (*input == '-') ? 1 : 0;
	if (!option)
		opt->path = input;
	else
	{
		input++;
		while (*input)
		{
			if (*input == 'l')
				opt->l = 1;
			else if (*input == 'R')
				opt->R = 1;
			else if (*input == 'a')
				opt->a = 1;
			else if (*input == 'r')
				opt->r = 1;
			else if (*input == 't')
				opt->t = 1;
			input++;
		}
	}
}

void reset_options(t_options *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->path = NULL;
}


int main(int argc, char **argv)
{
	char *input;
	int i;
	t_options opt;

	if (argc > 1)
	{
		reset_options(&opt);
		i = 1;
		while (argv[i])
		{
			input = argv[i];
			capture_input(input, &opt);
			i++;
		}
	}

	return (0);
}
