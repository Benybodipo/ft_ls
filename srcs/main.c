/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <besteba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:07:03 by besteba           #+#    #+#             */
/*   Updated: 2018/09/25 11:52:57 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		main(int argc, char **argv)
{
	char		*input;
	int			i;
	t_options	opt;
	t_file_info	*info;

	reset_options(&opt);
	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			input = argv[i];
			capture_input(input, &opt);
			i++;
		}
		opt.path = (!opt.path) ? "." : opt.path;
		info = set_file_info(opt.path, opt);
	}
	else
		info = set_file_info(".", opt);
	traverse(&info, opt);
	if (opt.rec)
		recursion(info, opt);
	return (0);
}
